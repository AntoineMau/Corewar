/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:04:24 by judumay           #+#    #+#             */
/*   Updated: 2019/06/26 14:31:55 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**prendre en compte le label et linstruction
*/

int		ft_check_more(t_struct *s, int nb, int i)
{
	int	j;

	j = s->i;
	if (i == 0)
	{
		while (s->tab_line[j])
		{
			if (s->tab_line[j][0] == '#')
				break ;
			j++;
		}
		s->error = j != nb ? ERROR_BAD_PARAM_NB : 0;
	}
	if (i == 1)
	{
		s->error = s->tab_line[nb] && s->tab_line[nb][0] != '#'
		? ERROR_BAD_PARAM_NB : 0;
	}
	return (s->error);
}

void	ft_one_arg(t_struct *s, int i)
{
	s->error = ERROR_BAD_PARAM_NAME;
	s->beg->size += 1;
	s->error = 0;
	ft_check_more(s, 2 + s->i, 0) ? ft_error(s->error, s, NULL) : 0;
	if (i == 1 && (s->beg->opcode = LIVE) && ft_check_direct(s, 1, 1, 4))
		s->beg->size += 0;
	else if (i == 2 && (s->beg->opcode = ZJMP) && ft_check_direct(s, 1, 1, 2))
		s->beg->size += 0;
	else if (i == 3 && (s->beg->opcode = FORK) && ft_check_direct(s, 1, 1, 2))
		s->beg->size += 0;
	else if (i == 4 && (s->beg->opcode = LFORK) && ft_check_direct(s, 1, 1, 2))
		s->beg->size += 0;
	else if (i == 5 && (s->beg->opcode = AFF) && ft_check_registre(s, 1, 1))
	{
		s->beg->size++;
		s->beg->ocp = ft_ocp(s->beg->param_code[0], 0, 0);
	}
	else
		ft_error(s->error, s, NULL);
	ft_check_more(s, 2 + s->i, 1) ? ft_error(s->error, s, NULL) : 0;
}
