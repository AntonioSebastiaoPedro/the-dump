/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:25:39 by aamandio          #+#    #+#             */
/*   Updated: 2026/06/04 13:20:06 by paulcard         ###   ########.fr       */
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

void	switch_weapon_next(t_cub *cub)
{
	cub->current_weapon_index++;
	if (cub->current_weapon_index >= WEAPON_COUNT)
		cub->current_weapon_index = 0;
	cub->current_weapon = &cub->weapons[cub->current_weapon_index];
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
