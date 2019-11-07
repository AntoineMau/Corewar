/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:24:59 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 12:15:50 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_lld(t_vm *vm, unsigned int arg_value[3]
	, unsigned int arg_size[3])
{
	int		i;

	if (arg_size[0] == T_DIR)
		vm->proc->r[arg_value[1]] = arg_value[0];
	else if (arg_size[0] == T_IND && (arg_size[0] = 2))
	{
		i = vm->proc->pc - arg_size[0] - arg_size[1] - 1;
		vm->proc->r[arg_value[1]] = vm->arena[i % MEM_SIZE][0] << 24
			| vm->arena[(i + 1) % MEM_SIZE][0] << 16
			| vm->arena[(i + 2) % MEM_SIZE][0] << 8
			| vm->arena[(i + 3) % MEM_SIZE][0];
	}
	vm->proc->carry = !vm->proc->r[arg_value[1]] ? 1 : 0;
}

void		op_lld(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	int				jump;

	(*pc) = (*pc + 1) % MEM_SIZE;
	jump = *pc;
	jump += recup_opc(vm->arena[*pc][0], arg_size, 4, 2) % MEM_SIZE;
	if (ft_opcode(vm, arg_value, arg_size, 4)
	&& (arg_size[0] == T_DIR || arg_size[0] == T_IND)
	&& arg_size[1] == T_REG)
	{
		exec_lld(vm, arg_value, arg_size);
		ft_visu_d_message(vm, "lld");
	}
	else
		*pc = jump;
}
