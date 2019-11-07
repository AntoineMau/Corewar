/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_three_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 09:48:28 by judumay           #+#    #+#             */
/*   Updated: 2019/06/26 15:37:54 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_three_args_suite(t_struct *s, int i)
{
	if (i == 5 && (s->beg->opcode = XOR)
		&& (ft_check_registre(s, 1, 0) || ft_check_index(s, 1, 0)
			|| ft_check_direct(s, 1, 0, 4)) && (ft_check_registre(s, 2, 0)
			|| ft_check_index(s, 2, 0) || ft_check_direct(s, 2, 0, 4))
		&& ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (i == 6 && (s->beg->opcode = LDI)
		&& (ft_check_registre(s, 1, 0) || ft_check_index(s, 1, 0)
		|| ft_check_direct(s, 1, 0, 2)) && (ft_check_registre(s, 2, 0)
			|| ft_check_direct(s, 2, 0, 2)) && ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (i == 7 && (s->beg->opcode = STI)
		&& ft_check_registre(s, 1, 0) && (ft_check_registre(s, 2, 0)
			|| ft_check_index(s, 2, 0) || ft_check_direct(s, 2, 0, 2))
			&& (ft_check_direct(s, 3, 1, 2) || ft_check_registre(s, 3, 1)))
		s->beg->size += 0;
	else if (i == 8 && (s->beg->opcode = LLDI)
		&& (ft_check_registre(s, 1, 0) || ft_check_index(s, 1, 0)
			|| ft_check_direct(s, 1, 0, 2)) && (ft_check_registre(s, 2, 0)
			|| ft_check_direct(s, 2, 0, 2)) && ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else
		ft_error(s->error, s, NULL);
	return (1);
}

static int	ft_three_args_s(t_struct *s, int i)
{
	if (i == 2 && (s->beg->opcode = SUB) && ft_check_registre(s, 1, 0)
		&& ft_check_registre(s, 2, 0) && ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (i == 3 && (s->beg->opcode = AND)
		&& (ft_check_registre(s, 1, 0) || ft_check_index(s, 1, 0)
			|| ft_check_direct(s, 1, 0, 4)) && (ft_check_registre(s, 2, 0)
			|| ft_check_index(s, 2, 0) || ft_check_direct(s, 2, 0, 4))
		&& ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (i == 4 && (s->beg->opcode = OR)
		&& (ft_check_registre(s, 1, 0) || ft_check_index(s, 1, 0)
			|| ft_check_direct(s, 1, 0, 4)) && (ft_check_registre(s, 2, 0)
			|| ft_check_index(s, 2, 0) || ft_check_direct(s, 2, 0, 4))
		&& ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (ft_three_args_suite(s, i))
		s->beg->size += 0;
	else
		ft_error(s->error, s, NULL);
	return (1);
}

void		ft_three_args(t_struct *s, int i)
{
	s->error = ERROR_BAD_PARAM_NAME;
	s->beg->size += 2;
	ft_check_more(s, 4 + s->i, 0) ? ft_error(s->error, s, NULL) : 0;
	if (i == 1 && (s->beg->opcode = ADD) && ft_check_registre(s, 1, 0)
		&& ft_check_registre(s, 2, 0) && ft_check_registre(s, 3, 1))
		s->beg->size += 0;
	else if (ft_three_args_s(s, i))
		s->beg->size += 0;
	else
		ft_error(s->error, s, NULL);
	ft_check_more(s, 4 + s->i, 1) ? ft_error(s->error, s, NULL) : 0;
	s->beg->ocp = ft_ocp(s->beg->param_code[0], s->beg->param_code[1]
		, s->beg->param_code[2]);
}
