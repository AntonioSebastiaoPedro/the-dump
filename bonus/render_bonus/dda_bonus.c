/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:25:16 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 18:21:33 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	has_door_collision(t_cub *cub, t_ray *ray)
{
	t_door	*door;

	door = NULL;
	if (cub->map->grid[ray->map_y][ray->map_x] == 'D')
	{
		door = get_door_at(cub, ray->map_x, ray->map_y);
		if (door && door->state == DOOR_CLOSED)
		{
			ray->is_door = 1;
			ray->hit = 1;
			return (1);
		}
	}
	return (0);
}

void	dda(t_ray *ray, t_cub *cub)
{
	ray->hit = 0;
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
		if (ray->map_x < 0 || ray->map_x >= cub->map->width || ray->map_y < 0
			|| ray->map_y >= cub->map->height)
			return ((void)(ray->hit = 1));
		if (has_door_collision(cub, ray))
			return ;
		if (cub->map->grid[ray->map_y][ray->map_x] == '1')
			return ((void)(ray->hit = 1));
	}
}
