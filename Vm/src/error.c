/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:34:57 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 16:05:32 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_fill_tab_err(char *tab_err[12])
{
	tab_err[0] = "open";
	tab_err[1] = "read";
	tab_err[2] = "close";
	tab_err[3] = "magic";
	tab_err[4] = "label";
	tab_err[5] = "Bad utilisation -> Options";
	tab_err[6] = "nb live";
	tab_err[7] = "name len";
	tab_err[8] = "comm len";
	tab_err[9] = "Size of the program";
	tab_err[10] = "end dump option";
	tab_err[11] = "malloc";
}

void		ft_error(int err, int nb_line, t_vm *vm)
{
	char	*tab_err[20];

	if (vm->option_visu == 1)
	{
		endwin();
		vm->visu.arena ? free(vm->visu.arena) : 0;
		vm->visu.hud ? free(vm->visu.hud) : 0;
		vm->option_visu_d ? free(vm->visu.desc) : 0;
		vm->visu.winner ? free(vm->visu.winner) : 0;
	}
	if (vm->beg != NULL)
		free_chaine(vm->beg);
	ft_fill_tab_err(tab_err);
	if (nb_line == -1)
		ft_dprintf(2, "error : %d || %s\n", err, tab_err[err]);
	else if (err == ERROR_NB_LIVE)
		ft_dprintf(2, "Player %d didn't show enough lives\n", nb_line);
	else if (err == ERROR_PROG_SIZE)
		ft_dprintf(2, "error : %d || %s\n",
		err, tab_err[err]);
	else
		ft_dprintf(2, "error : %d || %s, line %d\n",
		err, tab_err[err], nb_line);
	exit(0);
}

int			recup_opc(unsigned char opc, unsigned int *arg_size,
				int size_dir, int arg)
{
	int				i;
	unsigned char	tab[3];
	unsigned int	jump;

	jump = 0;
	tab[0] = opc / 64;
	opc %= 64;
	tab[1] = opc / 16;
	opc %= 16;
	tab[2] = opc / 4;
	i = -1;
	while (++i < 3 && !(arg_size[i] = 0))
		if (i < arg && tab[i] == REG_CODE && (arg_size[i] = T_REG))
			jump += 1;
		else if (i < arg && tab[i] == DIR_CODE && (arg_size[i] = T_DIR))
			jump += size_dir;
		else if (i < arg && tab[i] == IND_CODE && (arg_size[i] = T_IND))
			jump += 2;
	return (jump);
}

static void	ft_ternaire_arg(t_vm *vm, unsigned int *arg_value,
			int i, int size_dir)
{
	(vm->proc->pc) = (vm->proc->pc + size_dir) % MEM_SIZE;
	arg_value[i] = size_dir == 4
		? vm->arena[(vm->proc->pc - 3) % MEM_SIZE][0] << 24
			| vm->arena[(vm->proc->pc - 2) % MEM_SIZE][0] << 16
			| vm->arena[(vm->proc->pc - 1) % MEM_SIZE][0] << 8
			| vm->arena[vm->proc->pc][0]
		: vm->arena[(vm->proc->pc - 1) % MEM_SIZE][0] << 8
			| vm->arena[vm->proc->pc][0];
}

int			ft_opcode(t_vm *vm, unsigned int *arg_value, unsigned int *arg_size,
				int size_dir)
{
	int		i;
	int		ret;

	i = -1;
	ret = 1;
	while (++i < 3 && !(arg_value[i] = 0))
		if (arg_size[i] == T_REG)
		{
			(vm->proc->pc) = (vm->proc->pc + 1) % MEM_SIZE;
			arg_value[i] = vm->arena[vm->proc->pc][0] - 0x01;
			if (arg_value[i] > 15)
				ret = 0;
		}
		else if (arg_size[i] == T_DIR)
			ft_ternaire_arg(vm, arg_value, i, size_dir);
		else if (arg_size[i] == T_IND)
		{
			(vm->proc->pc) = (vm->proc->pc + 2) % MEM_SIZE;
			arg_value[i] = vm->arena[(vm->proc->pc - 1) % MEM_SIZE][0] << 8
				| vm->arena[vm->proc->pc][0];
		}
	return (ret);
}
