/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:45:43 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/02 02:47:08 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	count_door(t_cub *cub)
{
	int	n_door;
	int	i;
	int	j;

	n_door = 0;
	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (j < cub->map->width)
		{
			if (cub->map->grid[i][j] == 'D')
				n_door++;
			j++;
		}
		i++;
	}
	return (n_door);
}

void	add_door(t_cub *cub, int x, int y)
{
	cub->door[cub->n_door].x = x;
	cub->door[cub->n_door].y = y;
	cub->door[cub->n_door].state = DOOR_CLOSED;
	cub->door[cub->n_door].frame = 0;
	cub->door[cub->n_door].timer = 0;
	cub->n_door++;
}

int	init_door(t_cub *cub)
{
	int	x;
	int	y;

	cub->n_door = 0;
	cub->door = (t_door *)malloc(count_door(cub) * sizeof(t_door));
	if (!cub->door)
		return (0);
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (cub->map->grid[y][x] == 'D')
				add_door(cub, x, y);
			x++;
		}
		y++;
	}
	return (1);
}
