/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:16:31 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/20 16:52:58 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Visualizar gradiente
void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int	y;
	int	shade;
	int	color;

	y = 0;

	// teto
	while (y < ray->draw_start)
	{
		ft_put_pixel(cub, col, y, cub->config->ceiling_color);
		y++;
	}

	// parede (com gradiente baseado no wall_x)
	shade = (int)(ray->wall_impact * 255);
	color = (shade << 16) | (shade << 8) | shade;

	while (y <= ray->draw_end)
	{
		ft_put_pixel(cub, col, y, color);
		y++;
	}

	// chão
	while (y < HEIGHT)
	{
		ft_put_pixel(cub, col, y, cub->config->floor_color);
		y++;
	}
}
/*void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		ft_put_pixel(cub, col, y, cub->config->ceiling_color);
		y++;
	}
	while (y <= ray->draw_end)
	{
		if (ray->side == 1)
			ft_put_pixel(cub, col, y, 0xAAAAAA);
		else
			ft_put_pixel(cub, col, y, WHITE);
		y++;
	}
	while (y < HEIGHT)
	{
		ft_put_pixel(cub, col, y, cub->config->floor_color);
		y++;
	}
}*/
