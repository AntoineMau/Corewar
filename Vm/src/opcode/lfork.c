/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:12 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/02 14:21:41 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_lfork(t_vm *vm, unsigned int arg_value[3])
{
	int		i;
	t_proc	*new;

	if (!(new = malloc(sizeof(t_proc))))
		ft_error(ERROR_MALLOC, -1, vm);
	new->creation = vm->cycle;
	new->last_live = vm->proc->last_live;
	new->alive = vm->proc->alive;
	new->carry = vm->proc->carry;
	new->head = vm->proc->head;
	new->n_champ = vm->proc->n_champ;
	new->number = ++vm->nb_proc;
	new->pc = (vm->proc->pc - T_DIR + arg_value[0]) % MEM_SIZE;
	i = -1;
	while (++i < 16)
		new->r[i] = vm->proc->r[i];
	new->wait = vm->proc->wait;
	new->next = vm->beg;
	vm->beg = new;
}

void		op_lfork(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];

	(void)(*pc);
	arg_size[0] = T_DIR;
	arg_size[1] = 0;
	arg_size[2] = 0;
	if (ft_opcode(vm, arg_value, arg_size, 2))
	{
		exec_lfork(vm, arg_value);
		ft_visu_d_message(vm, "lfork");
	}
}
