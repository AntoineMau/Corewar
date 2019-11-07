/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:30 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 15:25:17 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_ldi(t_vm *vm, unsigned int arg_value[3],
	unsigned arg_size[3])
{
	int		realpc;
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
	realpc = (vm->proc->pc - arg_size[0] - arg_size[1] - arg_size[2] - 1)
		% MEM_SIZE;
	vm->proc->r[arg_value[2]] =
		vm->arena[idx_mod(realpc, index)][0] << 24
		| vm->arena[idx_mod(realpc, index + 1)][0] << 16
		| vm->arena[idx_mod(realpc, index + 2)][0] << 8
		| vm->arena[idx_mod(realpc, index + 3)][0];
	vm->proc->carry = vm->proc->r[arg_value[2]] == 0 ? 1 : 0;
}

void		op_ldi(t_vm *vm, unsigned int *pc)
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
		exec_ldi(vm, arg_value, arg_size);
		ft_visu_d_message(vm, "ldi");
	}
	else
		*pc = jump;
}
