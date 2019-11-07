/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instru.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 10:19:35 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 15:00:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	metttre a jour les octets
**	TOUT PEUT ETRE COLLE : l1:live%:100 (valide)
**	bien verif les deux " sur le header -> segfault
*/

static int	ft_check_direct_number(t_struct *s, int j, int last, int save)
{
	int octet;

	octet = s->k;
	s->k = 1;
	if ((s->tab_line[j][0] = '0') && s->tab_line[j][1]
		&& s->tab_line[j][1] <= '9' && s->tab_line[j][1] >= '0'
		&& ft_check_value(s, last, j) && (s->beg->size += octet))
	{
		if (!(s->beg->params[save - 1] = ft_strsub(s->tab_line[j]
			, 1, ft_strlen(s->tab_line[j]) - 2 + last)))
			ft_error(ERROR_MALLOC, s, NULL);
		return (1);
	}
	else if ((s->tab_line[j][0] = '0') && s->tab_line[j][1] && s->tab_line[j][2]
		&& s->tab_line[j][1] == '-' && s->tab_line[j][2] <= '9'
		&& s->tab_line[j][2] >= '0' && ft_check_value(s, last, j)
			&& (s->beg->size += octet))
	{
		if (!(s->beg->params[save - 1] = ft_strsub(s->tab_line[j]
			, 1, ft_strlen(s->tab_line[j]) - 2 + last)))
			ft_error(ERROR_MALLOC, s, NULL);
		return (1);
	}
	return (0);
}

static int	ft_check_direct_s(t_struct *s, int j, int last, int save)
{
	int octet;

	octet = s->k;
	s->k = 1;
	if (s->tab_line[j][1] && s->tab_line[j][1] == ':'
		&& ft_read_labelin(s, last, save, octet))
	{
		if (!(s->beg->params[save - 1] = ft_strsub(s->tab_line[j]
			, 1, ft_strlen(s->tab_line[j]) - 2 + last)))
			ft_error(ERROR_MALLOC, s, NULL);
		return (1);
	}
	s->k = octet;
	if (ft_check_direct_number(s, j, last, save))
		return (1);
	return (0);
}

int			ft_check_direct(t_struct *s, int i, int last, int octet)
{
	int	j;

	s->k = 0;
	j = i + s->i;
	s->beg->param_code[i - 1] = DIR_CODE;
	s->beg->param_size[i - 1] = octet;
	if (s->tab_line[j][0] == '%')
	{
		s->k = octet;
		if (ft_check_direct_s(s, j, last, i))
			return (1);
	}
	return (0);
}

static int	ft_check_registre_suite(t_struct *s, int last, int j)
{
	if (s->tab_line[j][0] != 'r' || (last && ft_strlen(s->tab_line[j]) != 2
		&& ft_strlen(s->tab_line[j]) != 3))
		return (0);
	if (!last && ft_strlen(s->tab_line[j]) != 3
		&& ft_strlen(s->tab_line[j]) != 4)
		return (0);
	return (1);
}

int			ft_check_registre(t_struct *s, int i, int last)
{
	int j;
	int save;

	save = i - 1;
	j = i + s->i;
	s->beg->param_code[i - 1] = REG_CODE;
	s->beg->param_size[i - 1] = 1;
	i = 1;
	if (!ft_check_registre_suite(s, last, j))
		return (0);
	if (s->tab_line[j][1] < '1' || s->tab_line[j][1] > '9')
		return (0);
	else if (s->tab_line[j][1] == '1' && s->tab_line[j][2]
		&& s->tab_line[j][2] != SEPARATOR_CHAR && (i++)
		&& (s->tab_line[j][2] < '0' || s->tab_line[j][2] > '6'))
		return (0);
	if ((last && s->tab_line[j][i + 1])
		|| (!last && (s->tab_line[j][i + 1] != SEPARATOR_CHAR
			|| s->tab_line[j][i + 2])))
		return (0);
	if (!(s->beg->params[save] = ft_strsub(s->tab_line[j]
		, 0, ft_strlen(s->tab_line[j]) - 1 + last)))
		ft_error(ERROR_MALLOC, s, NULL);
	s->beg->size += 1;
	return (1);
}
