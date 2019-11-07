/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabouce <mabouce@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:27:41 by judumay           #+#    #+#             */
/*   Updated: 2019/06/25 14:10:40 by mabouce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_is_label_chars(char c, t_struct *s)
{
	char	*label_chars;
	int		i;

	i = -1;
	if (!(label_chars = ft_strdup(LABEL_CHARS)))
		ft_error(ERROR_MALLOC, s, NULL);
	while (label_chars[++i])
		if (c == label_chars[i])
		{
			free(label_chars);
			return (1);
		}
	free(label_chars);
	return (0);
}

/*
**fonction qui permet de savoir si le premier arg est un label ou non.
**Elle retourne zero si ce n'est pas le cas mais que ca pourrait etre un autre
**type d'arg. Sinon Error. Retourne pos = 0 si pas de label et
**pos = tailledulabel + 1 sinon
*/

int	ft_first_is_label(char *str, t_struct *s)
{
	int		i;
	int		badlabelchar;

	i = 0;
	badlabelchar = 0;
	while (str[i] && str[i] != LABEL_CHAR)
	{
		if (!ft_is_label_chars(str[i], s))
			badlabelchar = 1;
		i++;
	}
	if (str[i] && str[i] == LABEL_CHAR)
	{
		if (i == 0)
			ft_error(ERROR_BAD_LABEL_NAME, s, NULL);
		if (str[i + 1] && str[i + 1] == LABEL_CHAR)
			return (0);
		if (badlabelchar == 1)
			return (0);
		return (i + 1);
	}
	return (0);
}
