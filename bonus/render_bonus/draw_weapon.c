/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:35:35 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/29 03:03:06 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	draw_weapon(t_cub *cub)
{
	t_texture		*texture;
	int				start_x;
	int				start_y;
	unsigned int	color;
	double			scale;
	int				scaled_width;
	int				scaled_height;

	texture = &cub->weapon.frames[cub->weapon.state][cub->weapon.current_frame];
	scale = 4.0;
	scaled_width = texture->width * scale;
	scaled_height = texture->height * scale;
	start_x = (WIDTH - scaled_width) / 2;
	start_y = HEIGHT - scaled_height;
	int	x = 0;
	int	y = 0;
	while (x < scaled_width)
	{
		y = 0;
		while (y < scaled_height)
		{
			color = get_texture_color(texture, x / scale, y / scale);
			if (color != WEAPON_BACKGROUND)
				ft_put_pixel(cub, start_x + x, start_y + y, color);
			y++;
		}
		x++;
	}
}
