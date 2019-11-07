/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_label.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:04:04 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 15:49:37 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_find_label_in(char *str, t_struct *s, int last)
{
	char	*label_chars;
	int		i;
	int		sep;
	int		j;

	i = 0 + s->k;
	sep = 0;
	if (!(label_chars = ft_strdup(LABEL_CHARS)))
		ft_error(ERROR_MALLOC, s, NULL);
	while (str[++i] && !(j = 0))
	{
		while (label_chars[j] && label_chars[j] != str[i])
			j++;
		if (!last && str[i] == SEPARATOR_CHAR)
			sep++;
		if ((last && str[i] == SEPARATOR_CHAR) || (!label_chars[j]
				&& ((str[i] == SEPARATOR_CHAR && sep > 1)
					|| str[i] != SEPARATOR_CHAR)))
		{
			free(label_chars);
			ft_error(ERROR_BAD_LABEL_NAME, s, NULL);
		}
	}
	free(label_chars);
	return (i);
}

int			ft_read_labelin(t_struct *s, int last, int save, int octet)
{
	int	i;
	int	j;

	j = save + s->i;
	i = ft_find_label_in(s->tab_line[j], s, last);
	i > 1 && !last ? i-- : 0;
	if ((last && s->tab_line[j][i]) || (!last && (s->tab_line[j][i] != ','
		|| s->tab_line[j][i + 1])))
		return (0);
	i = s->tab_line[j][0] == '%' ? 1 : 0;
	save--;
	if (!(s->beg->label[save] = ft_strsub(s->tab_line[j]
		, i + 1, ft_strlen(s->tab_line[j]) - i - 2 + last)))
		ft_error(ERROR_MALLOC, s, NULL);
	s->beg->size += octet;
	s->beg->pos_label[save] = s->beg->size;
	return (1);
}

int			ft_check_value(t_struct *s, int last, int j)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	i = (s->tab_line[j][i] == '-' && (++k) ? 1 : 0);
	i = (s->tab_line[j][i + 1] == '-' && (++k) ? 2 : i);
	if (k == 2)
		return (0);
	while (s->tab_line[j][i] && s->tab_line[j][i] != ','
		&& s->tab_line[j][i] >= '0' && s->tab_line[j][i] <= '9')
		i++;
	if ((!last && !s->tab_line[j][i]) || (last && s->tab_line[j][i]))
		return (0);
	i = s->k - 1;
	while (s->tab_line[j][++i] && (s->tab_line[j][i] >= '0'
			|| s->tab_line[j][i] <= '9' || (s->tab_line[j][i] == '-'
				&& i == s->k + 1)))
		if (i > 19 + s->k && (s->error = ERROR_LENGHT_NUMBER))
			return (0);
	if (((s->tab_line[j][i] && last == 1) || (s->tab_line[j][i] && last == 0
		&& s->tab_line[j][i] != ',')) && (s->error = ERROR_BAD_PARAM_NAME))
		return (0);
	return (1);
}

static int	ft_check_index_label(t_struct *s, int save, int last, int j)
{
	if (s->tab_line[j][0] == ':' && ft_read_labelin(s, last, save + 1, 2))
	{
		s->beg->params[save] = ft_strsub(s->tab_line[j]
			, 0, ft_strlen(s->tab_line[j]) - 1 + last);
		return (1);
	}
	s->beg->index = 0;
	return (0);
}

int			ft_check_index(t_struct *s, int i, int last)
{
	int j;
	int save;

	save = i - 1;
	s->k = 0;
	j = i + s->i;
	s->beg->param_code[i - 1] = IND_CODE;
	s->beg->param_size[i - 1] = 2;
	s->beg->index = 1;
	if (((s->tab_line[j][0] <= '9' && s->tab_line[j][0] >= '0')
		|| (s->tab_line[j][0] == '-'
		&& s->tab_line[j][1] <= '9' && s->tab_line[j][1] >= '0'))
		&& ft_check_value(s, last, j))
	{
		s->beg->params[save] = ft_strsub(s->tab_line[j]
			, 0, ft_strlen(s->tab_line[j]) - 1 + last);
		s->beg->size += 2;
		return (1);
	}
	return (ft_check_index_label(s, save, last, j) ? 1 : 0);
}
