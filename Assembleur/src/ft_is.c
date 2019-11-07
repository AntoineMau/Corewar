/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:03:06 by judumay           #+#    #+#             */
/*   Updated: 2019/06/26 14:01:58 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_is_instru_two(char *nsline, int pos)
{
	if (!ft_strncmp(nsline + pos, "aff", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "or", 2))
		return (pos + 2);
	if (!ft_strncmp(nsline + pos, "ld", 2))
		return (pos + 2);
	if (!ft_strncmp(nsline + pos, "st", 2))
		return (pos + 2);
	return (pos);
}

int				ft_is_instru(char *nsline, int pos)
{
	if (!ft_strncmp(nsline + pos, "lfork", 5))
		return (pos + 5);
	if (!ft_strncmp(nsline + pos, "zjmp", 4))
		return (pos + 4);
	if (!ft_strncmp(nsline + pos, "live", 4))
		return (pos + 4);
	if (!ft_strncmp(nsline + pos, "fork", 4))
		return (pos + 4);
	if (!ft_strncmp(nsline + pos, "lldi", 4))
		return (pos + 4);
	if (!ft_strncmp(nsline + pos, "add", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "sub", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "and", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "sti", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "xor", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "ldi", 3))
		return (pos + 3);
	if (!ft_strncmp(nsline + pos, "lld", 3))
		return (pos + 3);
	return (ft_is_instru_two(nsline, pos));
}

int				ft_is_separator(char *nsline, int pos)
{
	if (nsline[pos] && nsline[pos] == SEPARATOR_CHAR)
		return (pos + 1);
	return (pos);
}

int				ft_is_reg(char *nsline, int pos)
{
	if (nsline[pos] && nsline[pos] == 'r')
	{
		if (!nsline[pos + 1] || nsline[pos + 1] < '1' || nsline[pos + 1] > '9')
			return (pos);
		if (ft_chck(nsline[pos + 2]))
			return (pos + 2);
		if (nsline[pos + 1] == '1' && nsline[pos + 2] && nsline[pos + 2] <= '6'
			&& nsline[pos + 2] >= '0' && ft_chck(nsline[pos + 3]))
			return (pos + 3);
	}
	return (pos);
}

int				ft_is_comment(char *nsline, int pos)
{
	int pos2;

	pos2 = pos;
	if (nsline[pos2] && nsline[pos2] == COMMENT_CHAR)
	{
		pos2++;
		while (nsline[pos2])
			pos2++;
		return (pos2);
	}
	return (pos);
}
