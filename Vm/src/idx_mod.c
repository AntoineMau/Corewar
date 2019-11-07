/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:26:13 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 11:49:47 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	idx_mod(unsigned int realpc, unsigned int jump)
{
	jump %= 65536;
	return (jump > 32768 ? (realpc - (-jump % IDX_MOD)) % MEM_SIZE
		: (realpc + jump % IDX_MOD) % MEM_SIZE);
}
