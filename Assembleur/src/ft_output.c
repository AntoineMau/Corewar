/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:52:07 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 10:55:55 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_output(char *name_asm, t_header header, t_struct *s
				, unsigned char *core)
{
	int		fd;
	char	*str;

	if (!(str = malloc(ft_strlen(name_asm) + 1)))
		ft_error(ERROR_MALLOC, s, NULL);
	ft_bzero(str, ft_strlen(name_asm) + 1);
	ft_strncpy(str, name_asm, ft_strlen(name_asm) - 1);
	if (!(str = ft_strdjoin(str, "cor")))
		ft_error(ERROR_MALLOC, s, NULL);
	if ((fd = open(str, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 00644)) == -1)
		ft_error(ERROR_OPEN, s, NULL);
	if (write(fd, &header, sizeof(t_header)) == -1)
		ft_error(ERROR_WRITE, s, NULL);
	if (write(fd, core, s->size) == -1)
		ft_error(ERROR_WRITE, s, NULL);
	if (close(fd) == -1)
		ft_error(ERROR_CLOSE, s, NULL);
	free(str);
}

void	ft_make_line_dispatch(t_struct *s, int *j, int *i
									, unsigned char *str)
{
	if (s->beg->params[*i][0] == 'r')
		str[(*j)++] = ft_atoi(s->beg->params[*i] + 1);
	else if (ft_strisnum(s->beg->params[*i]) && (s->k = 1))
		*j = ft_dispatch(s, *j, *i, str);
	else if (s->beg->params[*i][0] == '-' && s->beg->params[*i] + 1
		&& ft_strisnum(s->beg->params[*i] + 1) && (s->k = 1))
		*j = ft_dispatch(s, *j, *i, str);
	else
		*j = ft_dispatch(s, *j, *i, str);
}

void	ft_make_line(t_struct *s, unsigned char *str)
{
	int j;
	int	i;

	j = 0;
	s->beg = s->first;
	s->label = s->first_label;
	s->i = 0;
	while (s->beg)
	{
		if (s->beg->opcode && (i = -1))
		{
			s->nb_line = s->beg->line;
			str[j++] = s->beg->opcode;
			s->beg->ocp != 0 ? str[j++] = s->beg->ocp : 0;
			while (++i < 3 && s->beg->params[i])
			{
				s->k = 0;
				ft_make_line_dispatch(s, &j, &i, str);
			}
		}
		s->i += s->beg->size;
		s->beg = s->beg->next;
	}
}
