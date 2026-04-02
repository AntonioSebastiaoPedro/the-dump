/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:42:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/02 12:52:29 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static void	init_ray(t_ray *ray, t_player *player, int x, int w)
{
	ray->camera_x = 2 * x / (double)w - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calc_step_side(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < map->height
			&& ray->map_x >= 0
			&& ray->map_x < map->width
			&& map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall(t_ray *ray, int h)
{
	if (ray->side == 0)
	{
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		if (ray->step_x > 0)
			ray->side_hit = 2;
		else
			ray->side_hit = 3;
	}
	else
	{
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
		if (ray->step_y > 0)
			ray->side_hit = 0;
		else
			ray->side_hit = 1;
	}
	if (ray->perp_wall_dist < 0.0001)
		ray->perp_wall_dist = 0.0001;
	ray->line_height = (int)(h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + h / 2;
	if (ray->draw_end >= h)
		ray->draw_end = h - 1;
	if (ray->side == 0)
		ray->color = RED;
	else
		ray->color = DARK_RED;
}

void	draw_walls(t_cub *cub)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < cub->mlx->width)
	{
		init_ray(&ray, cub->player, x, cub->mlx->width);
		calc_step_side(&ray, cub->player);
		perform_dda(&ray, cub->map);
		calc_wall(&ray, cub->mlx->height);
		draw_ver_line(cub, x, &ray);
		x++;
	}
}
