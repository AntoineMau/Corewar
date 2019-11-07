/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:12:02 by judumay           #+#    #+#             */
/*   Updated: 2019/08/22 14:42:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_error_msg(int err)
{
	err == 1 ? ft_putstr_fd("ERROR_OPEN", 2) : 0;
	err == 2 ? ft_putstr_fd("ERROR_READ", 2) : 0;
	err == 3 ? ft_putstr_fd("ERROR_WRITE", 2) : 0;
	err == 4 ? ft_putstr_fd("ERROR_CLOSE", 2) : 0;
	err == 5 ? ft_putstr_fd("ERROR_MALLOC", 2) : 0;
	err == 6 ? ft_putstr_fd("ERROR_NB_ARG", 2) : 0;
	err == 7 ? ft_putstr_fd("ERROR_HEADER", 2) : 0;
	err == 8 ? ft_putstr_fd("ERROR_LEN_COMM, (max lenght = 2048)", 2) : 0;
	err == 9 ? ft_putstr_fd("ERROR_LEN_NAME, (max lenght = 128)", 2) : 0;
	err == 10 ? ft_putstr_fd("ERROR_HEAD_COMM", 2) : 0;
	err == 11 ? ft_putstr_fd("ERROR_HEAD_NAME", 2) : 0;
	err == 12 ? ft_putstr_fd("ERROR_MULT_COMM", 2) : 0;
	err == 13 ? ft_putstr_fd("ERROR_MULT_NAME", 2) : 0;
	err == 14 ? ft_putstr_fd("ERROR_WRONG_FILE", 2) : 0;
	err == 15 ? ft_putstr_fd("ERROR_HEAD_NO_COMM", 2) : 0;
	err == 16 ? ft_putstr_fd("ERROR_HEAD_NO_NAME", 2) : 0;
	err == 17 ? ft_putstr_fd("ERROR_BAD_LABEL", 2) : 0;
	err == 18 ? ft_putstr_fd("ERROR_BAD_INSTRU_NAME", 2) : 0;
	err == 19 ? ft_putstr_fd("ERROR_BAD_PARAM_NAME", 2) : 0;
	err == 20 ? ft_putstr_fd("ERROR_BAD_COMMA", 2) : 0;
	err == 21 ? ft_putstr_fd("ERROR_BAD_PARAM_NB", 2) : 0;
	err == 22 ? ft_putstr_fd("ERROR_BAD_LABEL_NAME", 2) : 0;
	err == 23 ? ft_putstr_fd("ERROR_NO_CODE_FOR_CHAMPION", 2) : 0;
	err == 24 ? ft_putstr_fd("ERROR_LENGHT_NUMBER", 2) : 0;
	err == 25 ? ft_putstr_fd("ERROR_NEWLINE", 2) : 0;
}

static void	ft_clear_list_asm(t_asm **begin_list)
{
	t_asm	*save;
	int		i;

	save = *begin_list;
	while ((*begin_list))
	{
		i = -1;
		save = (*begin_list);
		(*begin_list) = (*begin_list)->next;
		while (++i < 3)
			save->label[i] ? free(save->label[i]) : 0;
		i = -1;
		while (++i < 3)
			save->params[i] ? free(save->params[i]) : 0;
		free(save);
	}
}

static void	ft_clear_list_label(t_label **begin_list)
{
	t_label	*save;

	save = *begin_list;
	while ((*begin_list))
	{
		save = (*begin_list);
		(*begin_list) = (*begin_list)->next;
		free(save->name);
		free(save);
	}
}

void		ft_finish(t_struct *s)
{
	get_next_line(s->fd, NULL);
	s->line ? ft_strdel(&s->line) : 0;
	s->tab ? ft_strtabdel(&s->tab) : 0;
	s->nsline ? free(s->nsline) : 0;
	s->beg = s->first;
	s->label = s->first_label;
	s->beg ? ft_clear_list_asm(&s->beg) : 0;
	s->label ? ft_clear_list_label(&s->label) : 0;
	s->str ? free(s->str) : 0;
	s ? free(s) : 0;
}

void		ft_error(int err, t_struct *s, char **str)
{
	if (s && err == ERROR_HEAD_NAME)
		s->nb_line = s->name;
	if (s && err == ERROR_HEAD_COMM)
		s->nb_line = s->comment;
	ft_dprintf(2, RED"error"DEF": %d -> ", err);
	ft_error_msg(err);
	(!s || s->nb_line < 0 || err == ERROR_MALLOC || err == ERROR_HEAD_NO_NAME
		|| err == ERROR_HEAD_NO_COMM) ? ft_dprintf(2, "\n")
		: ft_dprintf(2, " at line %d\n", s->nb_line);
	str != NULL ? ft_strtabdel(&str) : 0;
	ft_finish(s);
	exit(err);
}
