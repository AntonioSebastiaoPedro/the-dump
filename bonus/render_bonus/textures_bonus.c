/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:50:16 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 18:48:27 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static void	calculate_wall_impact(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_impact = player->pos_y + ray->dir_y * ray->perp_wall_dist;
	else
		ray->wall_impact = player->pos_x + ray->dir_x * ray->perp_wall_dist;
	ray->wall_impact = ray->wall_impact - (int)ray->wall_impact;
	if (ray->side == 0 && ray->dir_x < 0)
		ray->wall_impact = 1.0 - ray->wall_impact;
	if (ray->side == 1 && ray->dir_y > 0)
		ray->wall_impact = 1.0 - ray->wall_impact;
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
	ray->texture_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step_texture;
}
