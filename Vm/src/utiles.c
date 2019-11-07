/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 12:32:36 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 14:43:11 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_init_vm_suite(t_vm *vm)
{
	int i;
	int j;

	i = -1;
	while (++i < vm->nb_champ)
	{
		vm->proc->last_live = 0;
		vm->proc->alive = 0;
		vm->proc->carry = 0;
		vm->proc->creation = 0;
		vm->proc->number = ++vm->nb_proc;
		j = -1;
		while (++j < REG_NUMBER)
			vm->proc->r[j] = j == 0 ? 0xFFFFFFFF - i : 0;
		vm->nb_live_champ[i] = 0;
		vm->proc->wait = vm->cycle;
		if (i + 1 < vm->nb_champ)
		{
			if (!(vm->proc->next = malloc(sizeof(t_proc))))
				ft_error(ERROR_MALLOC, -1, vm);
			vm->proc = vm->proc->next;
		}
	}
}

void		ft_init_vm(t_vm *vm)
{
	int		i;

	vm->total_to_die = 0;
	vm->nb_proc = 0;
	vm->nb_check_cycle = 0;
	i = -1;
	while (++i < MEM_SIZE && !(vm->arena[i][0] = 0))
		vm->arena[i][1] = 0;
	if (!(vm->proc = malloc(sizeof(t_proc))))
		ft_error(ERROR_MALLOC, -1, vm);
	vm->beg = vm->proc;
	ft_init_vm_suite(vm);
	vm->proc->next = NULL;
	vm->proc = vm->beg;
	vm->cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	tab_wait_set(vm);
}

static void	ft_winner(t_vm *vm)
{
	t_proc	*winner;
	t_proc	*current;

	winner = vm->beg;
	current = vm->beg->next;
	while (current)
	{
		if (winner->last_live <= current->last_live)
			winner = current;
		current = current->next;
	}
	vm->option_visu == 1 ? ft_victory_visu(vm, winner) : 0;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->n_champ, winner->head.prog_name);
	free_chaine(vm->beg);
	exit(0);
}

static void	ft_cdt_suite(t_vm *vm)
{
	int		i;
	t_proc	*current;

	current = vm->beg;
	i = 0;
	if (vm->cycle_to_die == 0 && vm->cycle++)
		ft_winner(vm);
	while (current && !current->alive && ++i)
		current = current->next;
	i == ft_list_count_vm(vm->beg) ? ft_winner(vm) : 0;
	current = vm->beg;
	while (current)
	{
		if (current->alive == 0)
			ft_dead_proc(vm, &current);
		else
		{
			current->alive = 0;
			current = current->next;
		}
	}
	i = -1;
	while (++i < vm->nb_champ)
		vm->nb_live_champ[i] = 0;
}

void		ft_cycle_to_die(t_vm *vm)
{
	int				i;
	t_proc			*current;
	unsigned int	save;

	i = 0;
	save = vm->cycle_to_die;
	current = vm->beg;
	while (current && ((i += current->alive) >= 0))
		current = current->next;
	vm->total_to_die += vm->cycle_to_die;
	vm->nb_check_cycle++;
	if (i > NBR_LIVE || vm->nb_check_cycle == MAX_CHECKS)
	{
		vm->cycle_to_die = CYCLE_DELTA > vm->cycle_to_die
			? 0 : vm->cycle_to_die - CYCLE_DELTA;
		vm->nb_check_cycle = 0;
	}
	save != vm->cycle_to_die && vm->option_verbose >= 2 && !vm->option_visu
		&& !vm->option_visu_d
		? ft_printf("Cycle to die is now %d\n", vm->cycle_to_die) : 0;
	vm->option_visu == 1 ? refresh_cycle_to_die(vm) : 0;
	ft_cdt_suite(vm);
}
