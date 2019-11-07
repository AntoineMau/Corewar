/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:16 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 15:31:46 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			visual_sti(t_vm *vm, int index)
{
	int		i;
	char	*str;

	i = 4;
	while (--i >= 0)
	{
		mvwprintw(vm->visu.arena, 1 + ((3 * ((index + i) % MEM_SIZE)) / 192),
			2 + ((3 * ((index + i) % MEM_SIZE)) % 192),
			(str = get_hexa(vm->arena[(index + i) % MEM_SIZE][0])));
		ft_strdel(&str);
		mvwchgat(vm->visu.arena, 1 + ((3 * ((index + i) % MEM_SIZE)) / 192), 2 +
			((3 * ((index + i) % MEM_SIZE)) % 192), 2, A_BOLD,
			vm->arena[(index + i) % MEM_SIZE][1], 0);
	}
	wrefresh(vm->visu.arena);
	ft_visu_d_message(vm, "sti");
}

static void			exec_sti_suite(t_vm *vm, unsigned int index,
	unsigned int arg_value[3])
{
	int				i;
	unsigned int	tmp;

	tmp = vm->proc->r[arg_value[0]];
	i = 4;
	while (--i >= 0)
	{
		vm->arena[(index + i) % MEM_SIZE][0] = tmp % 256;
		vm->arena[(index + i) % MEM_SIZE][1] = vm->proc->n_champ;
		tmp >>= 8;
	}
}

static unsigned int	exec_sti(t_vm *vm, unsigned int arg_value[3],
	unsigned int arg_size[3], unsigned int index)
{
	unsigned int	realpc;

	index = 0;
	if (arg_size[1] == T_REG)
		index += vm->proc->r[arg_value[1]];
	else if (arg_size[1] == T_DIR)
		index += arg_value[1];
	else if (arg_size[1] == T_IND && (arg_size[1] = 2))
		index += vm->arena[arg_value[1]][0] << 24
			| vm->arena[arg_value[1] + 1][0] << 16
			| vm->arena[arg_value[1] + 2][0] << 8
			| vm->arena[arg_value[1] + 3][0];
	if (arg_size[2] == T_REG)
		index += vm->proc->r[arg_value[2]];
	else if (arg_size[2] == T_DIR)
		index += arg_value[2];
	realpc = (vm->proc->pc - (arg_size[0] + arg_size[1] + arg_size[2] + 1))
		% MEM_SIZE;
	index = idx_mod(realpc, index);
	exec_sti_suite(vm, index, arg_value);
	return (index);
}

void				op_sti(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	unsigned int	index;
	int				jump;

	(*pc) = (*pc + 1) % MEM_SIZE;
	jump = *pc;
	index = 0;
	jump += recup_opc(vm->arena[*pc][0], arg_size, 2, 3) % MEM_SIZE;
	if (ft_opcode(vm, arg_value, arg_size, 2)
	&& arg_size[0] == T_REG
	&& (arg_size[1] == T_REG || arg_size[1] == T_DIR || arg_size[1] == T_IND)
	&& (arg_size[2] == T_REG || arg_size[2] == T_DIR))
	{
		index = exec_sti(vm, arg_value, arg_size, index);
		vm->option_visu == 1 ? visual_sti(vm, index) : 0;
	}
	else
		*pc = jump;
}
