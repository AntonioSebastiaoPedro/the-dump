/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:25:39 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 16:02:29 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	on_mouse_click(t_cub *cub)
{
	if (cub->weapon.state == WEAPON_SHOT)
		return ;
	set_weapon_state(&cub->weapon, WEAPON_SHOT);
	play_weapon_sound(cub);
}

int	mouse_hook(int key, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (key == 1 && cub->mouse.show_mouse == false)
		on_mouse_click(cub);
	return (0);
}
