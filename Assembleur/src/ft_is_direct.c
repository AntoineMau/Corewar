/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:30:31 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 11:47:56 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_is_direct_digit(char *nsline, int pos, int pos2, t_struct *s)
{
	pos2++;
	if (nsline[pos2] && nsline[pos2] == LABEL_CHAR && (++pos2))
	{
		if (!nsline[pos2] || !ft_is_label_chars(nsline[pos2], s))
			ft_error(ERROR_BAD_PARAM_NAME, s, NULL);
		while (nsline[pos2] && ft_is_label_chars(nsline[pos2], s))
			pos2++;
		return (pos2);
	}
	else if (nsline[pos2] && ft_isdigit(nsline[pos2]))
	{
		while (nsline[pos2] && ft_isdigit(nsline[pos2]))
			pos2++;
		return (pos2);
	}
	else if (nsline[pos2] && nsline[pos2 + 1] && nsline[pos2] == '-'
		&& ft_isdigit(nsline[pos2 + 1]) && (++pos2))
	{
		while (nsline[pos2] && ft_isdigit(nsline[pos2]))
			pos2++;
		return (pos2);
	}
	else
		ft_error(ERROR_BAD_PARAM_NAME, s, NULL);
	return (pos);
}

int		ft_is_direct(char *nsline, int pos, t_struct *s)
{
	int pos2;

	pos2 = pos;
	if (nsline[pos2] && nsline[pos2] == DIRECT_CHAR)
		return (ft_is_direct_digit(nsline, pos, pos2, s));
	if (nsline[pos2] && ft_isdigit(nsline[pos2]))
	{
		while (nsline[pos2] && ft_isdigit(nsline[pos2]))
			pos2++;
		return (pos2);
	}
	else if (nsline[pos2] && nsline[pos2 + 1] && nsline[pos2] == '-'
		&& ft_isdigit(nsline[pos2 + 1]))
	{
		pos2++;
		while (nsline[pos2] && ft_isdigit(nsline[pos2]))
			pos2++;
		return (pos2);
	}
	return (pos);
}

int		ft_is_lab(char *nsline, int pos, t_struct *s)
{
	int pos2;

	pos2 = pos;
	if (nsline[pos2] && nsline[pos2] == LABEL_CHAR && (++pos2))
	{
		if (!nsline[pos2] || !ft_is_label_chars(nsline[pos2], s))
			ft_error(ERROR_BAD_PARAM_NAME, s, NULL);
		while (nsline[pos2] && ft_is_label_chars(nsline[pos2], s))
			pos2++;
		return (pos2);
	}
	return (pos);
}
