/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 07:19:05 by judumay           #+#    #+#             */
/*   Updated: 2019/09/23 13:31:13 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_check_file(t_struct *s)
{
	if (*s->line == '.')
		ft_error(ERROR_MULT_NAME, s, NULL);
	else
		ft_check_syntax(s);
}

static char		*ft_strtrimstart(char const *s)
{
	size_t	min;
	size_t	max;
	size_t	len;

	if (!s)
		return (NULL);
	min = 0;
	while (s[min] != '\0'
			&& (s[min] == ' ' || s[min] == '\n' || s[min] == '\t'))
		min++;
	max = ft_strlen(s);
	len = max - min;
	return (ft_strsub(s, min, len));
}

static void		ft_parcing_gnl_output(t_struct *s)
{
	if (s->check_last_line_valid == 1 && s->last_line_valid == 0)
		ft_error(ERROR_NEWLINE, s, NULL);
	if (s->ret < 0 && (s->nb_line = -1))
		ft_error(ERROR_READ, s, NULL);
	if (close(s->fd) == -1 && (s->nb_line = -1))
		ft_error(ERROR_CLOSE, s, NULL);
	if (s->ret == 0 && (s->nameok == 0 || s->commentok == 0))
		ft_error(ERROR_HEADER, s, NULL);
}

void			ft_check_last_line(t_struct *s)
{
	char *str;

	s->check_last_line_valid = 1;
	s->last_line_valid = 0;
	str = ft_strtrim(s->line);
	if (!str || !str[0] || str[0] == '#')
		s->last_line_valid = 1;
	ft_strdel(&s->line);
	free(str);
}

void			ft_parcing(t_header *header, t_struct *s)
{
	char				*tmp;

	if ((s->fd = open(s->av[s->ac - 1], O_RDONLY)) == -1)
		ft_error(ERROR_OPEN, s, NULL);
	while ((s->ret = get_next_line(s->fd, &s->line)) > 0)
	{
		tmp = !s->cfo && !s->nfo
			? ft_strtrimstart(s->line) : ft_strdup(s->line);
		free(s->line);
		s->line = tmp;
		if (*s->line == '#' || (!(*s->line) && s->cfo == 0 && s->nfo == 0))
			;
		else if (s->nameok == 0 || s->commentok == 0)
			ft_check_header(s, header);
		else
		{
			tmp = ft_strtrim(s->line);
			free(s->line);
			s->line = tmp;
			*s->line ? ft_check_file(s) : 0;
		}
		s->nb_line++;
		s->ret == 2 ? ft_check_last_line(s) : ft_strdel(&s->line);
	}
	ft_parcing_gnl_output(s);
}
