/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calcule_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:22:05 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 10:56:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_calcule_val_direct(t_struct *s, int i, long long *val)
{
	*val = ft_atolli(s->beg->params[i]);
	if (s->beg->param_size[i] == 2)
	{
		if (*val < 0)
			*val = 65536 + (*val % 65536);
		else if (*val > 0)
			*val = *val % 65536;
		*val == 0xffff + 1 ? val = 0 : 0;
	}
	else if (s->beg->param_size[i] == 4)
	{
		if (*val < 0)
			*val = 4294967296 + (*val % 4294967296);
		else if (*val > 0)
			*val = *val % 4294967296;
		*val == 0xffffffff + 1 ? *val = 0 : 0;
	}
}

long long		ft_calcule_val(t_struct *s, int i)
{
	long long	val;
	long long	val1;
	long long	val2;
	int			loop;

	loop = 0;
	if (s->k == 1)
		ft_calcule_val_direct(s, i, &val);
	else
	{
		while (s->label && ft_strcmp(s->label->name, s->beg->label[i]))
			s->label = s->label->next;
		if (!s->label)
			ft_error(ERROR_BAD_LABEL_NAME, s, NULL);
		val1 = s->label->pos;
		val2 = s->i;
		if (s->beg->param_size[i] == 2)
			val = val1 >= val2 ? val1 - val2 : val1 - val2 + 65536;
		else
			val = val1 >= val2 ? val1 - val2 : val1 - val2 + 4294967296;
		s->label = s->first_label;
	}
	val += loop;
	return (val);
}
