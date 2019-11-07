/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 13:11:02 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 11:10:17 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_compare_instruction(t_struct *s)
{
	s->beg->opcode = 0;
	!ft_strcmp(s->tab_line[s->i], "live") ? ft_one_arg(s, 1) : 0;
	!ft_strcmp(s->tab_line[s->i], "ld") ? ft_two_args(s, 1) : 0;
	!ft_strcmp(s->tab_line[s->i], "st") ? ft_two_args(s, 2) : 0;
	!ft_strcmp(s->tab_line[s->i], "add") ? ft_three_args(s, 1) : 0;
	!ft_strcmp(s->tab_line[s->i], "sub") ? ft_three_args(s, 2) : 0;
	!ft_strcmp(s->tab_line[s->i], "and") ? ft_three_args(s, 3) : 0;
	!ft_strcmp(s->tab_line[s->i], "or") ? ft_three_args(s, 4) : 0;
	!ft_strcmp(s->tab_line[s->i], "xor") ? ft_three_args(s, 5) : 0;
	!ft_strcmp(s->tab_line[s->i], "zjmp") ? ft_one_arg(s, 2) : 0;
	!ft_strcmp(s->tab_line[s->i], "ldi") ? ft_three_args(s, 6) : 0;
	!ft_strcmp(s->tab_line[s->i], "sti") ? ft_three_args(s, 7) : 0;
	!ft_strcmp(s->tab_line[s->i], "fork") ? ft_one_arg(s, 3) : 0;
	!ft_strcmp(s->tab_line[s->i], "lld") ? ft_two_args(s, 3) : 0;
	!ft_strcmp(s->tab_line[s->i], "lldi") ? ft_three_args(s, 8) : 0;
	!ft_strcmp(s->tab_line[s->i], "lfork") ? ft_one_arg(s, 4) : 0;
	!ft_strcmp(s->tab_line[s->i], "aff") ? ft_one_arg(s, 5) : 0;
	if (s->beg->opcode == 0)
		ft_error(ERROR_BAD_INSTRU_NAME, s, NULL);
}

static void	ft_put_label(t_struct *s)
{
	t_label	*new_l;

	new_l = ft_lst_create_label(s);
	if (!s->label && (s->label = new_l))
		s->first_label = s->label;
	else
	{
		s->label->next = new_l;
		s->label = s->label->next;
	}
	if (!(s->label->name = ft_strsub(s->tab_line[0]
		, 0, ft_strlen(s->tab_line[0]) - 1)))
		ft_error(ERROR_MALLOC, s, NULL);
	s->label->pos = s->size;
	s->i++;
}

void		ft_check_syntax(t_struct *s)
{
	t_asm	*new;

	new = ft_lst_create(s);
	if (!s->beg && (s->beg = new))
		s->first = s->beg;
	else
	{
		s->beg->next = new;
		s->beg = s->beg->next;
	}
	s->beg->line = s->nb_line;
	s->i = 0;
	s->tab_line = ft_set_args_to_tabs(s->line, s);
	ft_is_label(s) ? ft_put_label(s) : 0;
	s->tab_line[s->i] ? ft_compare_instruction(s) : 0;
	s->size += s->beg->size;
	ft_strtabdel(&s->tab_line);
	s->tab = NULL;
}
