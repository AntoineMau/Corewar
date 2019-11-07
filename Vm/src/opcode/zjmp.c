/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:25 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 13:45:44 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_zjmp(t_vm *vm, unsigned int arg_value[3])
{
	if (vm->proc->carry == 1)
		vm->proc->pc = idx_mod(vm->proc->pc - 3, arg_value[0]);
	vm->proc->pc %= MEM_SIZE;
}

void		op_zjmp(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];

	(void)(*pc);
	arg_size[0] = T_DIR;
	arg_size[1] = 0;
	arg_size[2] = 0;
	if (ft_opcode(vm, arg_value, arg_size, 2))
	{
		exec_zjmp(vm, arg_value);
		ft_visu_d_message(vm, "zjmp");
	}
}
