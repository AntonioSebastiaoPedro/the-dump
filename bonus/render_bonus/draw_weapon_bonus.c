/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:35:35 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 19:45:03 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	draw_weapon(t_cub *cub)
{
	t_texture		*texture;
	t_draw_weapon	dw;
	int				x;
	int				y;

	texture = &cub->current_weapon->frames[cub->current_weapon->state]
	[cub->current_weapon->current_frame];
	dw.scaled_width = texture->width * WEAPON_SCALE;
	dw.scaled_height = texture->height * WEAPON_SCALE;
	dw.start_x = (WIDTH - dw.scaled_width) / 2;
	dw.start_y = HEIGHT - dw.scaled_height;
	x = 0;
	while (x < dw.scaled_width)
	{
		y = 0;
		while (y < dw.scaled_height)
		{
			dw.color = get_texture_color(texture, x / WEAPON_SCALE,
					y / WEAPON_SCALE);
			if (dw.color != TRANSPARENT_BACKGROUND)
				ft_put_pixel(cub, dw.start_x + x, dw.start_y + y, dw.color);
			y++;
		}
		x++;
	}
}
