/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:24:51 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/02 13:41:56 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_aff(t_vm *vm, unsigned int arg_value[3])
{
	vm->option_visu == 0 && vm->option_visu_d == 0 && vm->option_dump <= 0
		? ft_printf("%c", vm->proc->r[arg_value[0]] % 256) : 0;
}

void		op_aff(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	int				jump;

	(*pc) = (*pc + 1) % MEM_SIZE;
	jump = *pc;
	jump += recup_opc(vm->arena[*pc][0], arg_size, 4, 1) % MEM_SIZE;
	if (ft_opcode(vm, arg_value, arg_size, 4)
	&& arg_size[0] == T_REG)
	{
		exec_aff(vm, arg_value);
		ft_visu_d_message(vm, "aff");
	}
	else
		*pc = jump;
}
