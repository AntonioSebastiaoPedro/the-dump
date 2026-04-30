/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 18:25:16 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/30 12:43:07 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

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
		{
			ray->hit = 1;
			break ;
		}
		if (cub->map->grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		if (cub->map->grid[ray->map_y][ray->map_x] == 'D')
		{
			ray->hit = 1;
			ray->is_door = 1;
		}
	}
}
