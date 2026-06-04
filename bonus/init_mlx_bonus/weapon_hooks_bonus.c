/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:25:39 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/05 10:49:56 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	on_mouse_click(t_cub *cub)
{
	if (!cub->current_weapon || cub->current_weapon->state == WEAPON_SHOT)
		return ;
	set_weapon_state(cub->current_weapon, WEAPON_SHOT);
	play_weapon_sound(cub);
	enemy_take_damage(cub);
}

int	mouse_hook(int key, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (cub->state == GAME)
	{
		if (key == 1 && cub->mouse.show_mouse == false)
			on_mouse_click(cub);
	}
	return (0);
}
