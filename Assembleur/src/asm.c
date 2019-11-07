/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 07:19:05 by judumay           #+#    #+#             */
/*   Updated: 2019/08/21 15:55:43 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_init_header(t_header *header)
{
	ft_bzero(header, sizeof(t_header));
	header->magic = COREWAR_EXEC_MAGIC;
	ft_invert_byte(&(header->magic));
}

int			main_asm(t_struct *s)
{
	t_header		header;
	char			*str;

	ft_init_header(&header);
	ft_check_arg(s);
	s->nb_line = 1;
	ft_parcing(&header, s);
	s->size == 0 ? ft_error(ERROR_NO_CODE, s, NULL) : 0;
	if (!(s->str = (unsigned char*)malloc(sizeof(unsigned char) * s->size + 1)))
		ft_error(ERROR_MALLOC, s, NULL);
	ft_bzero((void *)s->str, s->size);
	ft_make_line(s, s->str);
	header.prog_size = s->size;
	ft_invert_byte(&(header.prog_size));
	ft_output(s->av[s->ac - 1], header, s, s->str);
	if (!(str = malloc(ft_strlen(s->av[s->ac - 1]) + 3)))
		ft_error(ERROR_MALLOC, s, NULL);
	ft_bzero(str, ft_strlen(s->av[s->ac - 1]) + 3);
	ft_strncpy(str, s->av[s->ac - 1], ft_strlen(s->av[s->ac - 1]) - 1);
	if (!(str = ft_strdjoin(str, "cor")))
		ft_error(ERROR_MALLOC, s, NULL);
	miniprintf("Writing output program to %s\n", str);
	free(str);
	ft_finish(s);
	return (0);
}

int			main(int ac, char **av)
{
	t_struct		*s;

	if (!(s = (t_struct*)malloc(sizeof(t_struct))))
		ft_error(ERROR_MALLOC, s, NULL);
	ft_set_struct_core(s, ac, av);
	return (main_asm(s));
}
