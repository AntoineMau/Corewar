/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:26:13 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 15:12:30 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			visual_st(t_vm *vm, int index)
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
	ft_visu_d_message(vm, "st");
}

static unsigned int	exec_st(t_vm *vm, unsigned int arg_value[3],
	unsigned int arg_size[3], unsigned int index)
{
	unsigned int	i;
	unsigned int	tmp;

	if (arg_size[1] == T_REG)
		vm->proc->r[arg_value[1]] = vm->proc->r[arg_value[0]];
	else
	{
		arg_size[1] = T_DIR;
		index = arg_size[1] == T_REG ? vm->proc->r[arg_value[1]] : arg_value[1];
		index = idx_mod((vm->proc->pc - arg_size[0] - arg_size[1] - 1)
			% MEM_SIZE, index);
		tmp = vm->proc->r[arg_value[0]];
		i = 5;
		while (--i >= 1)
		{
			vm->arena[(index + i - 1) % MEM_SIZE][0] = tmp % 256;
			vm->arena[(index + i - 1) % MEM_SIZE][1] = vm->proc->n_champ;
			tmp >>= 8;
		}
	}
	return (index);
}

void				op_st(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	unsigned int	index;
	int				jump;

	(*pc) = (*pc + 1) % MEM_SIZE;
	jump = *pc;
	index = 0;
	jump += recup_opc(vm->arena[*pc][0], arg_size, 4, 2) % MEM_SIZE;
	if (ft_opcode(vm, arg_value, arg_size, 4)
	&& arg_size[0] == T_REG
	&& (arg_size[1] == T_REG || arg_size[1] == T_IND))
	{
		index = exec_st(vm, arg_value, arg_size, index);
		vm->option_visu == 1 ? visual_st(vm, index) : 0;
	}
	else
		*pc = jump;
}
