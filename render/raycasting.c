/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:40:10 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/14 16:42:04 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_ray_dir(t_cub *cub, t_ray *ray, int col)
{
	ray->camera_x = 2.0 * (double)col / (double)WIDTH - 1.0;
	ray->dir_x = cub->player->dir_x + (cub->player->plane_x * ray->camera_x);
	ray->dir_y = cub->player->dir_y + (cub->player->plane_y * ray->camera_x);
}

void	draw_vertical_line(t_cub *cub, int col, int line_height, int color)
{
	int	y;
	int	start_y;

	start_y = (HEIGHT - line_height) / 2;
	y = start_y;

	while (y < start_y + line_height)
	{
		ft_put_pixel(cub, col, y, color);
		y++;
	}
}
