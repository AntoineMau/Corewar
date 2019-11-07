/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_live.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 12:02:59 by judumay           #+#    #+#             */
/*   Updated: 2019/10/02 14:15:09 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	refresh_live_by_champ(t_vm *vm, unsigned int i)
{
	char	*str;
	t_proc	*current;

	current = vm->beg;
	while (current && i + 1 != current->n_champ)
		current = current->next;
	if (current && current->n_champ == i + 1)
	{
		wattron(vm->visu.hud, A_BOLD);
		mvwprintw(vm->visu.hud, 19 + (i * 4), 7, "Last live :          "
			"                                       ");
		mvwprintw(vm->visu.hud, 19 + (i * 4), 40,
			(str = ft_itoa(current->last_live)));
		ft_strdel(&str);
		mvwprintw(vm->visu.hud, 20 + (i * 4), 40, "                        ");
		if (vm->nb_live_champ[i] == 0)
			mvwprintw(vm->visu.hud, 20 + (i * 4), 40, "0");
		else
			mvwprintw(vm->visu.hud, 20 + (i * 4), 40,
				(str = ft_itoa(vm->nb_live_champ[i])));
		ft_strdel(&str);
		wattroff(vm->visu.hud, A_BOLD);
	}
}

int		ft_round_sup(double to_round)
{
	int	round;
	int	x;

	round = (int)to_round;
	to_round *= 10;
	x = (int)to_round;
	if (x > 0)
		round++;
	return (round);
}

void	refresh_live(t_vm *vm, int barre)
{
	int		i;
	int		j;
	double	tmp;
	int		total_live;

	i = -1;
	j = 0;
	total_live = 0;
	while (++i < vm->nb_champ && (total_live += vm->nb_live_champ[i]) >= 0)
		refresh_live_by_champ(vm, (unsigned int)i);
	i = -1;
	tmp = 0;
	while (total_live != 0 && j < 100)
		if (tmp == 0)
			tmp = ft_round_sup((vm->nb_live_champ[++i] * 100 / total_live));
		else
		{
			wattron(vm->visu.hud, COLOR_PAIR(i < vm->nb_champ ? i + 1 : 9));
			mvwprintw(vm->visu.hud, 20 + (vm->nb_champ * 4) + (barre * 3),
				6 + j++, "-");
			tmp--;
			wattroff(vm->visu.hud, COLOR_PAIR(i < vm->nb_champ ? i + 1 : 9));
		}
	wrefresh(vm->visu.hud);
}
