/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_args_to_tabs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 11:32:31 by judumay           #+#    #+#             */
/*   Updated: 2019/07/03 11:53:58 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**permet de calculer le nombre max d'instru + 1 pour les commentaires et + 1
**s'il y a un label ( si pos > 0 )
*/

int				ft_max_instru(char *line, int pos, t_struct *s)
{
	int	i;
	int	sep;
	int	nb_instru;

	nb_instru = 3;
	i = -1;
	sep = 0;
	if (pos > 0)
		nb_instru++;
	while (line[++i])
	{
		if (line[i] == COMMENT_CHAR)
			return (nb_instru + sep);
		if (line[i] == SEPARATOR_CHAR)
			sep++;
		if (sep > 2)
			ft_error(ERROR_BAD_COMMA, s, NULL);
	}
	return (nb_instru + sep);
}

int				ft_chck(char c)
{
	if (c == SEPARATOR_CHAR || c == '\0' || c == COMMENT_CHAR)
		return (1);
	return (0);
}

char			**ft_set_tab_char(t_struct *s)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (s->tabsize + 1))))
		ft_error(ERROR_MALLOC, s, NULL);
	while (i < s->tabsize + 1)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

/*
**Cette fonction permet de separer les arguments et les mettres chaqu'un dans
**une case de tab. Elle gere quelques erreurs egalement (trop de coma, mauvais
**label, mauvaises instru. retourne le tableau des arguments
*/

void			ft_set_args_to_tabs_dispatch(t_struct *s, int *pos, int *i)
{
	if (s->sav_pos != (*pos = ft_is_instru(s->nsline, *pos)))
		!(s->tab[(*i)++] = ft_strsub(s->nsline, s->sav_pos, *pos - s->sav_pos))
			? ft_error(ERROR_MALLOC, s, NULL) : 0;
	else if (s->sav_pos != (*pos = ft_is_separator(s->nsline, *pos)))
	{
		!(s->tab[*i - 1] = ft_strdjoinc(s->tab[*i - 1], s->nsline[*pos - 1]))
			? ft_error(ERROR_MALLOC, s, NULL) : 0;
	}
	else if (s->sav_pos != (*pos = ft_is_lab(s->nsline, *pos, s)))
	{
		!(s->tab[(*i)++] = ft_strsub(s->nsline, s->sav_pos, *pos - s->sav_pos))
			? ft_error(ERROR_MALLOC, s, NULL) : 0;
	}
	else if (s->sav_pos != (*pos = ft_is_reg(s->nsline, *pos)))
		!(s->tab[(*i)++] = ft_strsub(s->nsline, s->sav_pos, *pos - s->sav_pos))
			? ft_error(ERROR_MALLOC, s, NULL) : 0;
	else if (s->sav_pos != (*pos = ft_is_direct(s->nsline, *pos, s)))
		!(s->tab[(*i)++] = ft_strsub(s->nsline, s->sav_pos, *pos - s->sav_pos))
			? ft_error(ERROR_MALLOC, s, NULL) : 0;
	*pos = ft_is_comment(s->nsline, *pos);
	if (*pos == s->sav_pos)
		ft_error(ERROR_BAD_INSTRU_NAME, s, NULL);
}

char			**ft_set_args_to_tabs(char *line, t_struct *s)
{
	int		pos;
	int		i;

	i = 0;
	pos = ft_first_is_label(line, s);
	s->tabsize = ft_max_instru(line, pos, s);
	s->tab = ft_set_tab_char(s);
	pos > 0 && !(s->tab[i++] = ft_strsub(line, 0, pos))
			? ft_error(ERROR_MALLOC, s, s->tab) : 0;
	s->nsline = ft_strremove_char(line, " \t");
	while (s->nsline[pos])
	{
		if (i == s->tabsize)
			ft_error(ERROR_BAD_PARAM_NB, s, NULL);
		s->sav_pos = pos;
		ft_set_args_to_tabs_dispatch(s, &pos, &i);
	}
	free(s->nsline);
	s->nsline = NULL;
	return (s->tab);
}
