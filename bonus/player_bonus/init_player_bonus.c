/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:18:20 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/28 00:23:00 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

t_player	*init_player(t_cub *cub)
{
	if (!cub->player || !cub->player->dir)
		return (NULL);
	cub->player->is_moving = 0;
	set_dir_vectors(cub->player);
	return (cub->player);
}
