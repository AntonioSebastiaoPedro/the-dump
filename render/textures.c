/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:50:16 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/20 16:50:38 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calculate_wall_impact(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_impact = player->pos_y + ray->dir_y * ray->perp_wall_dist;
	else
		ray->wall_impact = player->pos_x + ray->dir_x * ray->perp_wall_dist;
	ray->wall_impact = ray->wall_impact - (int)ray->wall_impact;
}
