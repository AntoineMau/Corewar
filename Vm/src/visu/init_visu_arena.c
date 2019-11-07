/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu_arena.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:55:22 by judumay           #+#    #+#             */
/*   Updated: 2019/10/02 15:33:40 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	*get_hexa(int nb)
{
	char	*str;
	char	*base;

	if (nb < 0 || nb > 255)
		return (0);
	if (!(str = (char*)malloc(sizeof(char) * 3)))
		return (0);
	base = "0123456789abcdef";
	str[0] = base[nb / 16];
	str[1] = base[nb % 16];
	str[2] = 0;
	base = 0;
	return (str);
}

void	init_color_vm(void)
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_CYAN);
	init_pair(6, COLOR_WHITE, COLOR_RED);
	init_pair(7, COLOR_WHITE, COLOR_YELLOW);
	init_pair(8, COLOR_WHITE, COLOR_BLUE);
	init_pair(9, COLOR_BLACK, COLOR_BLACK);
}

void	init_champ_in_visu(t_vm *vm)
{
	int		i;
	int		color;
	char	*str;

	i = 0;
	while (i < MEM_SIZE * 3)
	{
		color = 9;
		mvwprintw(vm->visu.arena, 1 + (i / 192), 2 + (i % 192),
			(str = get_hexa(vm->arena[i / 3][0])));
		ft_strdel(&str);
		if (vm->arena[i / 3][1] != 0)
			color = vm->arena[i / 3][1];
		mvwchgat(vm->visu.arena, 1 + (i / 192), 2 + (i % 192), 2, A_BOLD,
			color, 0);
		mvwprintw(vm->visu.arena, 1 + (i / 192), 4 + (i % 192), " ");
		i += 3;
	}
}

void	ft_init_visu(t_vm *vm)
{
	bzero(&vm->visu, sizeof(t_visu));
	initscr();
	noecho();
	timeout(1);
	curs_set(0);
	init_color_vm();
	vm->visu.hud = newwin(66, 111, 0, 195);
	vm->visu.arena = newwin(66, 195, 0, 0);
	vm->option_i == 1 ? vm->visu.desc = newwin(18, 195, 66, 0) : 0;
	vm->visu.cps = 50;
	refresh();
	box(vm->visu.arena, 0, 0);
	box(vm->visu.hud, 0, 0);
	box(vm->visu.desc, 0, 0);
	init_champ_in_visu(vm);
	wrefresh(vm->visu.arena);
	vm->option_i == 1 ? add_description(vm) : 0;
	init_visual_hud(vm);
	get_key(vm);
}
