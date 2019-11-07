/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 08:23:23 by judumay           #+#    #+#             */
/*   Updated: 2019/06/25 14:14:18 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*ft_lst_create_label(t_struct *s)
{
	t_label	*new;

	if (!(new = (t_label *)malloc(sizeof(t_label))))
		ft_error(ERROR_MALLOC, s, NULL);
	new->pos = 0;
	new->name = NULL;
	new->next = NULL;
	return (new);
}

t_asm	*ft_lst_create(t_struct *s)
{
	t_asm	*new;

	if (!(new = (t_asm *)malloc(sizeof(t_asm))))
		ft_error(ERROR_MALLOC, s, NULL);
	ft_bzero(new, sizeof(t_asm));
	return (new);
}
