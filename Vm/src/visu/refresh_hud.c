/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_hud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:02:35 by judumay           #+#    #+#             */
/*   Updated: 2019/10/02 15:47:48 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		refresh_pc(t_vm *vm)
{
	t_proc	*pr;

	pr = vm->beg;
	while (pr)
	{
		mvwchgat(vm->visu.arena, 1 + ((pr->pc * 3) / 192)
		, 2 + ((pr->pc * 3) % 192), 2, A_REVERSE
		, vm->arena[pr->pc][1], 0);
		pr = pr->next;
	}
	wrefresh(vm->visu.arena);
	pr = vm->beg;
	while (pr)
	{
		if (vm->arena[pr->pc][1] == 0)
			mvwchgat(vm->visu.arena, 1 + ((pr->pc * 3) / 192)
			, 2 + ((pr->pc * 3) % 192), 2, A_BOLD
			, 10, 0);
		else
			mvwchgat(vm->visu.arena, 1 + ((pr->pc * 3) / 192)
			, 2 + ((pr->pc * 3) % 192), 2, A_BOLD
			, vm->arena[pr->pc][1], 0);
		pr = pr->next;
	}
}

void		visual_every_cycle(t_vm *vm)
{
	char	*str;

	str = ft_itoa(vm->cycle);
	wattron(vm->visu.hud, A_BOLD);
	mvwprintw(vm->visu.hud, 13, 13, str);
	ft_strdel(&str);
	wattroff(vm->visu.hud, A_BOLD);
	wrefresh(vm->visu.hud);
	get_key(vm);
}

int			ft_list_count_vm(t_proc *begin_list)
{
	int		i;
	t_proc	*current;

	i = 0;
	current = begin_list;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

void		refresh_process(t_vm *vm)
{
	char	*str;

	wattron(vm->visu.hud, A_BOLD);
	mvwprintw(vm->visu.hud, 15, 17, "      ");
	mvwprintw(vm->visu.hud, 15, 17,
		(str = ft_itoa(ft_list_count_vm(vm->beg))));
	ft_strdel(&str);
	wattroff(vm->visu.hud, A_BOLD);
	wrefresh(vm->visu.hud);
}
