/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:07 by anmauffr          #+#    #+#             */
/*   Updated: 2019/11/06 15:39:07 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_lldi(t_vm *vm, unsigned int arg_value[3],
	unsigned arg_size[3])
{
	int		index;

	index = 0;
	if (arg_size[0] == T_REG)
		index += vm->proc->r[arg_value[0]];
	else if (arg_size[0] == T_IND && (arg_size[0] = 2))
		index += vm->arena[arg_value[0]][0] << 24
			| vm->arena[arg_value[0] + 1][0] << 16
			| vm->arena[arg_value[0] + 2][0] << 8
			| vm->arena[arg_value[0] + 3][0];
	else
		index += arg_value[0];
	if (arg_size[1] == T_REG)
		index += vm->proc->r[arg_value[1]];
	else
		index += arg_value[1];
	vm->proc->r[arg_value[2]] =
		vm->arena[index][0] << 24
		| vm->arena[index + 1][0] << 16
		| vm->arena[index + 2][0] << 8
		| vm->arena[index + 3][0];
	vm->proc->carry = vm->proc->r[arg_value[2]] == 0 ? 1 : 0;
}

void		op_lldi(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	int				jump;

	(*pc) = (*pc + 1) % MEM_SIZE;
	jump = *pc;
	jump += recup_opc(vm->arena[*pc][0], arg_size, 2, 3) % MEM_SIZE;
	if (ft_opcode(vm, arg_value, arg_size, 2)
	&& (arg_size[0] == T_REG || arg_size[0] == T_DIR || arg_size[0] == T_IND)
	&& (arg_size[1] == T_REG || arg_size[1] == T_DIR)
	&& arg_size[2] == T_REG)
	{
		exec_lldi(vm, arg_value, arg_size);
		ft_visu_d_message(vm, "lldi");
	}
	else
		*pc = jump;
}
