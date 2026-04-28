/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_hooks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:25:39 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/28 16:27:04 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	on_mouse_click(t_cub *cub)
{
	if (cub->weapon.state == WEAPON_SHOT)
		return ;
	set_weapon_state(&cub->weapon, WEAPON_SHOT);
}

int	mouse_hook(int key, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (key == 1 && cub->mouse.show_mouse == false)
		on_mouse_click(cub);
	return (0);
}
