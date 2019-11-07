/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 07:16:25 by judumay           #+#    #+#             */
/*   Updated: 2019/09/23 13:31:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_get_first_line_name(t_struct *s, t_header *header)
{
	int		start;
	int		compteur;

	start = 4;
	compteur = 0;
	while (s->line[++start])
		if (s->line[start] == '\"' && ++compteur)
			break ;
	compteur != 1 ? ft_error(ERROR_HEAD_NAME, s, NULL) : 0;
	while (s->line[++start])
	{
		if (s->line[start] == '\"' && ++compteur)
			break ;
		header->prog_name[s->index++] = s->line[start];
	}
	if (compteur == 2 && (s->nameok = 1))
	{
		s->index > PROG_NAME_LENGTH ? ft_error(ERROR_LEN_NAME, s, NULL) : 0;
		ft_find_occu(s->line) == 0 ? ft_error(ERROR_HEAD_NAME, s, NULL) : 0;
	}
	else if ((s->nfo = 1))
		header->prog_name[s->index++] = '\n';
}

void		ft_get_others_line_name(t_struct *s, t_header *header)
{
	int		start;
	int		compteur;

	start = -1;
	compteur = 0;
	if (!s->line[start + 1])
	{
		header->prog_name[s->index++] = '\n';
		return ;
	}
	while (s->line[++start])
	{
		if (s->line[start] == '\"' && ++compteur)
			break ;
		header->prog_name[s->index++] = s->line[start];
	}
	if (compteur == 1)
	{
		s->index > PROG_NAME_LENGTH ? ft_error(ERROR_LEN_NAME, s, NULL) : 0;
		s->nfo = 0;
		s->nameok = 1;
		ft_find_occu(s->line) == 0 ? ft_error(ERROR_HEAD_NAME, s, NULL) : 0;
	}
	else
		header->prog_name[s->index++] = '\n';
}

void		ft_get_others_line_comment(t_struct *s, t_header *header)
{
	int		start;
	int		compteur;

	start = -1;
	compteur = 0;
	if (!s->line[start + 1])
	{
		header->comment[s->index++] = '\n';
		return ;
	}
	while (s->line[++start])
	{
		if (s->line[start] == '\"' && ++compteur)
			break ;
		header->comment[s->index++] = s->line[start];
	}
	if (compteur == 1)
	{
		s->index > COMMENT_LENGTH ? ft_error(ERROR_LEN_COMM, s, NULL) : 0;
		s->commentok = 1;
		ft_find_occu(s->line) == 0 ? ft_error(ERROR_HEAD_COMM, s, NULL) : 0;
		s->cfo = 0;
	}
	else
		header->comment[s->index++] = '\n';
}

void		ft_get_first_line_comm(t_struct *s, t_header *header)
{
	int		start;
	int		compteur;

	start = 8;
	compteur = 0;
	while (s->line[++start])
		if (s->line[start] == '\"' && ++compteur)
			break ;
	compteur != 1 ? ft_error(ERROR_HEAD_NAME, s, NULL) : 0;
	while (s->line[++start])
	{
		if (s->line[start] == '\"' && ++compteur)
			break ;
		header->comment[s->index++] = s->line[start];
	}
	if (compteur == 2)
	{
		s->index > COMMENT_LENGTH ? ft_error(ERROR_LEN_COMM, s, NULL) : 0;
		s->commentok = 1;
		ft_find_occu(s->line) == 0 ? ft_error(ERROR_HEAD_COMM, s, NULL) : 0;
	}
	else if ((s->cfo = 1))
		header->comment[s->index++] = '\n';
}
