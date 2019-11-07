/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:59:21 by judumay           #+#    #+#             */
/*   Updated: 2019/10/02 14:47:10 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_victory_visu_two(t_vm *vm, t_proc *winner)
{
	int i;

	wrefresh(vm->visu.winner);
	wattroff(vm->visu.winner, COLOR_PAIR(winner->n_champ));
	while (1)
	{
		timeout(0);
		if ((i = getch()) == ' ')
			break ;
	}
	timeout(1);
	endwin();
	ft_printf("Contestant %d, \"%s\", has won !\n",
		winner->n_champ, winner->head.prog_name, vm->cycle);
	free(vm->visu.arena);
	free(vm->visu.hud);
	vm->option_visu_d ? free(vm->visu.desc) : 0;
	free(vm->visu.winner);
	free_chaine(vm->beg);
	exit(0);
}

void		ft_victory_visu(t_vm *vm, t_proc *winner)
{
	vm->visu.winner = newwin(18, 111, 66, 195);
	box(vm->visu.winner, 0, 0);
	wattron(vm->visu.winner, COLOR_PAIR(winner->n_champ));
	mvwprintw(vm->visu.winner, 5, 25,
	" /$$      /$$ /$$$$$$ /$$   /$$ /$$   /$$ /$$$$$$$$ /$$$$$$$ ");
	mvwprintw(vm->visu.winner, 6, 25,
	"| $$  /$ | $$|_  $$_/| $$$ | $$| $$$ | $$| $$_____/| $$__  $$");
	mvwprintw(vm->visu.winner, 7, 25,
	"| $$ /$$$| $$  | $$  | $$$$| $$| $$$$| $$| $$      | $$  \\ $$");
	mvwprintw(vm->visu.winner, 8, 25,
	"| $$/$$ $$ $$  | $$  | $$ $$ $$| $$ $$ $$| $$$$$   | $$$$$$$/");
	mvwprintw(vm->visu.winner, 9, 25,
	"| $$$$_  $$$$  | $$  | $$  $$$$| $$  $$$$| $$__/   | $$__  $$");
	mvwprintw(vm->visu.winner, 10, 25,
	"| $$$/ \\  $$$  | $$  | $$\\  $$$| $$\\  $$$| $$      | $$  \\ $$");
	mvwprintw(vm->visu.winner, 11, 25,
	"| $$/   \\  $$ /$$$$$$| $$ \\  $$| $$ \\  $$| $$$$$$$$| $$  | $$");
	mvwprintw(vm->visu.winner, 12, 25,
	"|__/     \\__/|______/|__/  \\__/|__/  \\__/|________/|__/  |__/");
	mvwprintw(vm->visu.winner, 13, 25,
	"                                                             ");
	ft_victory_visu_two(vm, winner);
}

void		modif_cps(t_vm *vm, int to_add)
{
	char	*str;

	vm->visu.cps += to_add;
	if (vm->visu.cps > 1000)
		vm->visu.cps = 1000;
	else if (vm->visu.cps < 10)
		vm->visu.cps = 10;
	wattron(vm->visu.hud, A_BOLD);
	mvwprintw(vm->visu.hud, 11, 26, (str = ft_itoa(vm->visu.cps)));
	ft_strdel(&str);
	mvwprintw(vm->visu.hud, 11,
		26 + ft_strlen((str = ft_itoa(vm->visu.cps))), "    ");
	ft_strdel(&str);
	wrefresh(vm->visu.hud);
}

int			handle_pause(t_vm *vm, int *pause, int p_or_r)
{
	wattron(vm->visu.hud, A_BOLD);
	if (p_or_r == 1)
	{
		mvwprintw(vm->visu.hud, 5, 45, "**   PAUSE   **");
		(*pause) *= -1;
		wrefresh(vm->visu.hud);
	}
	else if (p_or_r == 2)
	{
		mvwprintw(vm->visu.hud, 5, 45, "**   PAUSE   **");
		(*pause) = 1;
		wrefresh(vm->visu.hud);
	}
	else
		mvwprintw(vm->visu.hud, 5, 45, "**  RUNNING  **");
	wattroff(vm->visu.hud, A_BOLD);
	return (1);
}

void		get_key(t_vm *vm)
{
	int			i;
	int			j;
	static int	pause = 1;

	while (1)
	{
		timeout(0);
		if ((i = getch()) == ' ')
			handle_pause(vm, &pause, 1);
		else if (i == 'p' && handle_pause(vm, &pause, 2))
			break ;
		else if ((j = ft_strfindc("erm", i)) >= 0 && vm->visu.cps < 1000)
			modif_cps(vm, ft_pow(10, j));
		else if ((j = ft_strfindc("wqn", i)) >= 0 && vm->visu.cps > 10)
			modif_cps(vm, -ft_pow(10, j));
		if (pause == -1 && handle_pause(vm, &pause, 0))
			break ;
	}
	timeout(1);
	if (vm->visu.cps < 500)
		usleep(1000000 / vm->visu.cps);
	else if (vm->visu.cps < 1000)
		usleep(100000 / vm->visu.cps);
}
