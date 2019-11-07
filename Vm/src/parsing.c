/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:29:17 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/02 14:14:16 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				ft_check_header(t_header head, unsigned char proc
	, t_vm *vm)
{
	int		len_nam;
	int		len_com;

	len_nam = ft_strlen(head.prog_name);
	len_com = ft_strlen(head.comment);
	if (head.magic != COREWAR_EXEC_MAGIC)
		ft_error(ERROR_MAGIC, proc, vm);
	else if (!len_nam || len_nam > PROG_NAME_LENGTH)
		ft_error(ERROR_NAME_LEN, proc, vm);
	else if (!head.prog_size || head.prog_size > CHAMP_MAX_SIZE)
		ft_error(ERROR_PROG_SIZE, proc, vm);
	else if (!len_com || len_com > COMMENT_LENGTH)
		ft_error(ERROR_COMM_LEN, proc, vm);
}

static unsigned char	ft_read(int fd, int proc, t_vm *vm, unsigned int j)
{
	int		ret;
	char	buf;

	if ((ret = read(fd, &buf, sizeof(char))) == -1)
		ft_error(ERROR_READ, proc, vm);
	ret == 0 && j != vm->proc->head.prog_size
		? ft_error(ERROR_PROG_SIZE, -1, vm) : 0;
	return (buf);
}

static void				ft_pars_header(int *fd, t_header *head, char *av
	, t_vm *vm)
{
	(*fd = open(av, O_RDONLY)) == -1 ? ft_error(ERROR_OPEN, -1, vm) : 0;
	read(*fd, head, sizeof(t_header)) == -1 ? ft_error(ERROR_READ, -1, vm) : 0;
	ft_invert_byte(&head->magic);
	ft_invert_byte(&head->prog_size);
}

static void				ft_parsing_suite(t_vm *vm)
{
	int				index;
	int				nb_player;
	unsigned int	j;
	char			buf;

	nb_player = -1;
	index = 0;
	while (++nb_player < vm->nb_champ)
	{
		j = 0;
		while (j++ < vm->proc->head.prog_size
			&& (vm->arena[index][1] = nb_player + 1))
			vm->arena[index++][0] = ft_read(vm->fd[nb_player]
				, nb_player + 1, vm, j);
		if (read(vm->fd[nb_player], &buf, sizeof(char)) != 0)
			ft_error(ERROR_PROG_SIZE, -1, vm);
		while (index < (nb_player + 1) * MEM_SIZE / vm->nb_champ
			&& !(vm->arena[index][1] = 0))
			vm->arena[index++][0] = 0;
		vm->proc = vm->proc->next;
	}
}

void					ft_parsing(t_vm *vm, char **av)
{
	int				index;
	int				nb_player;

	index = -1;
	vm->beg = vm->proc;
	while (++index < vm->nb_champ)
	{
		ft_pars_header(&vm->fd[index], &vm->proc->head, av[index], vm);
		ft_check_header(vm->proc->head, index + 1, vm);
		vm->proc->pc = index * (MEM_SIZE / vm->nb_champ);
		vm->proc->n_champ = index + 1;
		vm->proc = vm->proc->next;
	}
	vm->proc = vm->beg;
	ft_parsing_suite(vm);
	vm->proc = vm->beg;
	nb_player = -1;
	while (++nb_player < vm->nb_champ)
		close(vm->fd[nb_player]) == -1 ? ft_error(ERROR_CLOSE,
			nb_player + 1, vm) : 0;
}
