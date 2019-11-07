/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 19:42:22 by judumay           #+#    #+#             */
/*   Updated: 2019/06/24 12:09:12 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_set_struct_core(t_struct *s, int ac, char **av)
{
	ft_bzero(s, sizeof(t_struct));
	s->ac = ac;
	s->av = av;
}
