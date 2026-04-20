/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:40:10 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/21 00:10:31 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	calculate_wall_impact(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_impact = player->pos_y + ray->dir_y * ray->perp_wall_dist;
	else
		ray->wall_impact = player->pos_x + ray->dir_x * ray->perp_wall_dist;
	ray->wall_impact = ray->wall_impact - (int)ray->wall_impact;


	// entender inversao
	/*if (ray->side == 0 && ray->dir_x > 0) //ea
		ray->wall_impact = 1.0 - ray->wall_impact;
	if (ray->side == 1 && ray->dir_y < 0) // no
		ray->wall_impact = 1.0 - ray->wall_impact;*/
}

t_texture	*get_texture(t_ray *ray, t_cub *cub)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (&cub->textures->we);
		else
			return (&cub->textures->ea);
	}
	else
	{
		if (ray->dir_y < 0)
			return (&cub->textures->no);
		else
			return (&cub->textures->so);
	}
	return (NULL);
}

void	calculate_texture(t_ray *ray, t_cub *cub)
{
	t_texture	*texture;

	calculate_wall_impact(ray, cub->player);
	texture = get_texture(ray, cub);
	ray->texture_column = (int)(ray->wall_impact * texture->width);
	if (ray->texture_column < 0)
		ray->texture_column = 0;
	if (ray->texture_column >= texture->width)
		ray->texture_column = texture->width - 1;
	ray->step_texture = (double)texture->height / (double)ray->line_height;
	ray->texture_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->step_texture;
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
