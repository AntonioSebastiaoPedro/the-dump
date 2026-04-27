/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:40:10 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/25 14:42:19 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static void	calculate_ray_dir(int col, t_ray *ray, t_player *player)
{
	ray->camera_x = 2.0 * (double)col / (double)WIDTH - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
}

static void	calculate_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	calculate_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0.0)
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
	if (ray->dir_y < 0.0)
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

static void	calculate_wall(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.000001)
		ray->perp_wall_dist = 0.000001;
	ray->line_height = HEIGHT / ray->perp_wall_dist;
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	raycasting(int col, t_ray *ray, t_cub *cub)
{
	ray->map_x = (int)cub->player->pos_x;
	ray->map_y = (int)cub->player->pos_y;
	calculate_ray_dir(col, ray, cub->player);
	calculate_delta_dist(ray);
	calculate_side_dist(ray, cub->player);
	dda(ray, cub);
	calculate_wall(ray);
	calculate_texture(ray, cub);
	draw_vertical_line(col, ray, cub);
}
