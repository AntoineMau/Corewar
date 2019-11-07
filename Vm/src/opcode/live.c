/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:22:14 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 14:42:11 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_check_verbose(t_vm *vm, int j, t_proc *save)
{
	if (j >= 1 && vm->option_verbose >= 1 && vm->option_verbose <= 2
		&& !vm->option_visu && !vm->option_visu_d)
		ft_printf("Player %u (%s) is said to be alive\n",
			save->n_champ, save->head.prog_name);
}

static void	exec_live(t_vm *vm, unsigned int arg_value[3])
{
	int		i;
	int		j;
	t_proc	*current;
	t_proc	*save;

	j = 0;
	current = vm->beg;
	vm->proc->alive++;
	i = 1;
	while (i <= 4 && vm->nb_champ >= i && arg_value[0] != UINT32_MAX - i + 1)
		i++;
	if (i < 5)
	{
		vm->nb_live_champ[i - 1]++;
		while (current)
		{
			if (current && i == (int)current->n_champ && ++j)
			{
				current->last_live = vm->cycle + 1;
				save = current;
			}
			current = current->next;
		}
		ft_check_verbose(vm, j, save);
	}
}

void		op_live(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];

	(void)(*pc);
	arg_size[0] = T_DIR;
	arg_size[1] = 0;
	arg_size[2] = 0;
	if (ft_opcode(vm, arg_value, arg_size, 4))
	{
		exec_live(vm, arg_value);
		ft_visu_d_message(vm, "live");
	}
}
