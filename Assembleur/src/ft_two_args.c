/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:04:24 by judumay           #+#    #+#             */
/*   Updated: 2019/06/25 14:14:30 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**s->i correspond a la presence du label ou non
*/

void		ft_two_args(t_struct *s, int i)
{
	s->error = ERROR_BAD_PARAM_NAME;
	s->beg->size += 2;
	ft_check_more(s, 3 + s->i, 0) ? ft_error(s->error, s, NULL) : 0;
	if (i == 1 && (s->beg->opcode = LD) && ((ft_check_direct(s, 1, 0, 4)
			|| ft_check_index(s, 1, 0)) && ft_check_registre(s, 2, 1)))
		s->beg->size += 0;
	else if (i == 2 && (s->beg->opcode = ST) && ft_check_registre(s, 1, 0)
		&& (ft_check_registre(s, 2, 1) || ft_check_index(s, 2, 1)))
		s->beg->size += 0;
	else if (i == 3 && (s->beg->opcode = LLD) && (ft_check_index(s, 1, 0)
		|| ft_check_direct(s, 1, 0, 4)) && ft_check_registre(s, 2, 1))
		s->beg->size += 0;
	else
		ft_error(s->error, s, NULL);
	ft_check_more(s, 3 + s->i, 1) ? ft_error(s->error, s, NULL) : 0;
	s->beg->ocp = ft_ocp(s->beg->param_code[0], s->beg->param_code[1], 0);
}
