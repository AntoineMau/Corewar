/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:11:05 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/03 11:39:58 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		t_opcode_set(t_opcode t_opcode_array[17])
{
	t_opcode_array[0] = 0;
	t_opcode_array[1] = &op_live;
	t_opcode_array[2] = &op_ld;
	t_opcode_array[3] = &op_st;
	t_opcode_array[4] = &op_add;
	t_opcode_array[5] = &op_sub;
	t_opcode_array[6] = &op_and;
	t_opcode_array[7] = &op_or;
	t_opcode_array[8] = &op_xor;
	t_opcode_array[9] = &op_zjmp;
	t_opcode_array[10] = &op_ldi;
	t_opcode_array[11] = &op_sti;
	t_opcode_array[12] = &op_fork;
	t_opcode_array[13] = &op_lld;
	t_opcode_array[14] = &op_lldi;
	t_opcode_array[15] = &op_lfork;
	t_opcode_array[16] = &op_aff;
}

void		tab_wait_set(t_vm *vm)
{
	vm->tab_wait[0] = 1;
	vm->tab_wait[1] = 10;
	vm->tab_wait[2] = 5;
	vm->tab_wait[3] = 5;
	vm->tab_wait[4] = 10;
	vm->tab_wait[5] = 10;
	vm->tab_wait[6] = 6;
	vm->tab_wait[7] = 6;
	vm->tab_wait[8] = 6;
	vm->tab_wait[9] = 20;
	vm->tab_wait[10] = 25;
	vm->tab_wait[11] = 25;
	vm->tab_wait[12] = 800;
	vm->tab_wait[13] = 10;
	vm->tab_wait[14] = 50;
	vm->tab_wait[15] = 1000;
	vm->tab_wait[16] = 2;
}

void		ft_wait(t_vm *vm, unsigned char opcode)
{
	vm->proc->opcode = opcode;
	if (opcode > 0 && opcode < 17)
		vm->proc->wait = vm->cycle + vm->tab_wait[opcode];
	else
	{
		vm->proc->pc = (vm->proc->pc + vm->tab_wait[0]) % MEM_SIZE;
		vm->proc->wait = vm->cycle + vm->tab_wait[0];
	}
}

void		ft_visu_wait(t_vm *vm)
{
	char	*str;

	if (vm->option_visu_d == 1)
	{
		wattron(vm->visu.hud, A_BOLD);
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 61, "                                         ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 61, "Need to wait : ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 77, (str = ft_itoa(vm->proc->wait - vm->cycle)));
		ft_strdel(&str);
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 78 + ft_strlen((str = ft_itoa(vm->proc->wait - vm->cycle))),
			"cycles.");
		ft_strdel(&str);
		wrefresh(vm->visu.hud);
	}
}
