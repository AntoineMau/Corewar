/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:22:05 by judumay           #+#    #+#             */
/*   Updated: 2019/06/25 13:38:50 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				ft_dispatch_size_four(t_struct *s
	, unsigned char **str, char **hex)
{
	unsigned int	len;
	unsigned int	k;

	k = 0;
	*hex = ft_lltoabase_unsigned(s->val, 16);
	len = ft_strlen(*hex);
	if (len < 7)
		(*str)[s->j++] = 00;
	if (len < 5)
		(*str)[s->j++] = 00;
	if (len < 3)
		(*str)[s->j++] = 00;
	(*str)[s->j++] = !(len % 2) ? ft_hexatoi(*hex, 2) : ft_hexatoi(*hex, 1);
	k = 2 - (len % 2);
	while (k < len)
	{
		(*str)[s->j++] = ft_hexatoi(*hex + k, 2);
		k += 2;
	}
	ft_strdel(hex);
}

void				ft_dispatch_size_two(t_struct *s
	, unsigned char **str, char **hex)
{
	unsigned int	len;

	*hex = ft_lltoabase_unsigned(s->val, 16);
	len = ft_strlen(*hex);
	if (len < 3)
		(*str)[s->j++] = 00;
	(*str)[s->j++] = !(len % 2) ? ft_hexatoi(*hex, 2) : ft_hexatoi(*hex, 1);
	if (len >= 3)
		(*str)[s->j++] = ft_hexatoi(*hex + (2 - len % 2), 2);
	ft_strdel(hex);
}

int					ft_dispatch(t_struct *s, int j, int i, unsigned char *str)
{
	char			*hex;

	s->j = j;
	s->val = ft_calcule_val(s, i);
	if (s->beg->param_size[i] == 2)
		ft_dispatch_size_two(s, &str, &hex);
	else if (s->beg->param_size[i] == 4)
		ft_dispatch_size_four(s, &str, &hex);
	return (s->j);
}
