/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 13:27:44 by judumay           #+#    #+#             */
/*   Updated: 2019/09/23 09:43:58 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_ocp(int a, int b, int c)
{
	int	k;

	k = 0;
	k += a;
	k = k << 2;
	k += b;
	k = k << 2;
	k += c;
	k = k << 2;
	return (k);
}

void		ft_invert_byte(unsigned int *val)
{
	int				i;
	unsigned int	revnbr;
	unsigned int	nbr;

	i = 3;
	nbr = *val;
	while (i >= 0)
	{
		((char*)(&revnbr))[i] = ((char*)(&nbr))[0];
		nbr = nbr >> 8;
		i--;
	}
	*val = revnbr;
}

void		ft_check_arg(t_struct *s)
{
	int		len;

	len = ft_strlen(s->av[s->ac - 1]);
	if (len < 2 || s->av[s->ac - 1][len - 2] != '.'
		|| s->av[s->ac - 1][len - 1] != 's')
		ft_error(ERROR_WRONG_FILE, s, NULL);
}

static int	ft_find_label_char(t_struct *s)
{
	char	*label_chars;
	int		i;
	int		ok;
	int		j;

	ok = 0;
	i = -1;
	if (!(label_chars = ft_strdup(LABEL_CHARS)))
		ft_error(ERROR_MALLOC, s, NULL);
	while (s->tab_line[s->i][++i] && (j = -1))
	{
		if (s->tab_line[s->i][i] == LABEL_CHAR && ok == 1
			&& !s->tab_line[s->i][i + 1] && (i = -1))
			break ;
		else if (!(ok = 0) && s->tab_line[s->i][i] == LABEL_CHAR
			&& (i = -2))
			break ;
		while (label_chars[++j])
			label_chars[j] == s->tab_line[s->i][i] ? ok = 1 : 0;
		if (ok != 1 && (i = -2))
			break ;
	}
	free(label_chars);
	i == -2 ? ft_error(ERROR_BAD_LABEL, s, NULL) : 0;
	return (i == -1 ? 1 : 0);
}

int			ft_is_label(t_struct *s)
{
	if (s->tab_line[s->i][ft_strlen(s->tab_line[s->i]) - 1] != LABEL_CHAR)
		return (0);
	if (ft_find_label_char(s))
		return (1);
	ft_error(ERROR_BAD_LABEL, s, NULL);
	return (0);
}
