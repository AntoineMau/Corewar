/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 10:04:56 by judumay           #+#    #+#             */
/*   Updated: 2019/09/30 09:52:01 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		ft_visu_d_message(t_vm *vm, char *str)
{
	if (vm->option_visu_d == 1)
	{
		wattron(vm->visu.hud, A_BOLD);
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 +
			vm->nb_champ * 4, 61, "                                         ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 +
			vm->nb_champ * 4, 61, "Effectue un ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 +
			vm->nb_champ * 4, 73, str);
		wrefresh(vm->visu.hud);
	}
}

void		init_description(t_vm *vm)
{
	int		j;
	char	*str;
	t_proc	*current;

	j = -1;
	current = vm->beg;
	mvwprintw(vm->visu.hud, 26 + j * 2 + vm->nb_champ * 4, 50,
			"DERNIERE ACTION ENREGISTREE");
	while (++j < vm->nb_champ)
	{
		wattron(vm->visu.hud, COLOR_PAIR(j + 1));
		mvwprintw(vm->visu.hud, 26 + j * 2 + vm->nb_champ * 4, 40,
			(str = ft_strsub(current->head.prog_name, 0, 10)));
		ft_strdel(&str);
		mvwprintw(vm->visu.hud, 26 + j * 2 + vm->nb_champ * 4, 50, "   : ");
		wattroff(vm->visu.hud, COLOR_PAIR((j + 1)));
		current = current->next;
	}
}

static void	add_description_two(t_vm *vm)
{
	mvwprintw(vm->visu.desc, 10, 2, "lldi\t: Pareil que ldi, mais n applique "
	"aucun modulo aux adresses.");
	mvwprintw(vm->visu.desc, 11, 2, "or\t: Cette opération est un OU bit-à-bit"
	", suivant le même principe que and.");
	mvwprintw(vm->visu.desc, 12, 2, "st\t: Prend un registre et un registre ou"
	" un indirect, et stocke la valeur du registre vers le second paramètre.");
	mvwprintw(vm->visu.desc, 13, 2, "sti\t: Prend un registre, et deux index "
	". Additionne les deux derniers, utilise cette somme comme une adresse "
	"ou sera copiée la valeur du premier paramètre.");
	mvwprintw(vm->visu.desc, 14, 2, "sub\t: Pareil que add, et utilise une "
	"soustraction.");
	mvwprintw(vm->visu.desc, 15, 2, "xor\t: Fait comme and avec un "
	"OU exclusif.");
	mvwprintw(vm->visu.desc, 16, 2, "zjmp\t: Il prend un index et fait un saut "
	"à cette adresse si le carry est à 1.");
	wattroff(vm->visu.desc, A_BOLD);
	wrefresh(vm->visu.desc);
}

void		add_description(t_vm *vm)
{
	wattron(vm->visu.desc, A_BOLD);
	mvwprintw(vm->visu.desc, 1, 2, "add\t: Prend trois registres, additionne "
	"les 2 premiers, et met le résultat dans le troisième.");
	mvwprintw(vm->visu.desc, 2, 2, "aff\t: Prend un registre, dont le contenu"
	" est interprete comme la valeur ASCII d un caractère a afficher sur la "
	"sortie standard.");
	mvwprintw(vm->visu.desc, 3, 2, "and\t: Applique un & (ET bit-à-bit) sur les"
	" deux premiers parametres, et stocke le resultat dans le registre qui est "
	"le 3eme paramètre.");
	mvwprintw(vm->visu.desc, 4, 2, "fork\t: Prend un index, crée un nouveau "
	"processus, qui hérite des différents états de son père, à part son PC "
	"qui est mis a PC + 1er parametre modulo IDX_MOD");
	mvwprintw(vm->visu.desc, 5, 2, "ld\t: Prend un paramètre quelconque et un "
	"registre. Charge la valeur du premier paramètre dans le registre.");
	mvwprintw(vm->visu.desc, 6, 2, "ldi\t: Prend 2 index et 1 registre, "
	"additionne les 2 premiers, traite ca comme une adresse, y lit une valeur "
	"de la taille d un registre et la met dans le 3eme.");
	mvwprintw(vm->visu.desc, 7, 2, "lfork\t: Pareil qu un fork sans modulo à "
	"l madresse.");
	mvwprintw(vm->visu.desc, 8, 2, "live\t: L instruction qui permet à un "
	"processus de rester vivant. A également pour effet de rapporter que le "
	"joueur dont le numéro est en paramètre est en vie.");
	mvwprintw(vm->visu.desc, 9, 2, "lld\t: C est la même chose que ld, mais "
	"sans modulo à l adresse.");
	add_description_two(vm);
}
