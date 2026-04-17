/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:40:10 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/17 02:47:47 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_ray_dir(int col, t_ray *ray, t_player *player)
{
	ray->camera_x = 2.0 * (double)col / (double)WIDTH - 1.0;
	ray->dir_x = player->dir_x + (player->plane_x * ray->camera_x);
	ray->dir_y = player->dir_y + (player->plane_y * ray->camera_x);
}

void	calculate_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	calculate_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
		ray->step_x = -1;
	}
	else
	{
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
		ray->step_x = 1;
	}
	if (ray->dir_y < 0)
	{
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
		ray->step_y = -1;
	}
	else
	{
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
		ray->step_y = 1;
	}
}

void	setup_ray(t_cub *cub, t_ray *ray, int col)
{
	ray->map_x = (int)cub->player->pos_x;
	ray->map_y = (int)cub->player->pos_y;
	calculate_ray_dir(col, ray, cub->player);
	calculate_delta_dist(ray);
	calculate_side_dist(ray, cub->player);
}

/*void	draw_vertical_line(t_cub *cub, int col, int line_height, int color)
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
*/
