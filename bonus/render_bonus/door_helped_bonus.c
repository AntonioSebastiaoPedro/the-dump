/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_helped_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:48:47 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 10:50:39 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static int	count_doors(t_cub *cub)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (cub->map->grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	add_door(t_cub *cub, int x, int y)
{
	t_door	*door;

	door = &cub->door[cub->n_door];
	door->x = x;
	door->y = y;
	door->state = DOOR_CLOSED;
	door->frame = 0;
	door->timer = 0;
	cub->n_door++;
}

void	init_doors(t_cub *cub)
{
	int	total;
	int	y;
	int	x;

	total = count_doors(cub);
	cub->n_door = 0;
	if (total == 0)
		return ((void)(cub->door = NULL));
	cub->door = ft_calloc(total, sizeof(t_door));
	if (!cub->door)
		return ;
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
}

t_door	*get_door_at(t_cub *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->n_door)
	{
		if (cub->door[i].x == x && cub->door[i].y == y)
			return (&cub->door[i]);
		i++;
	}
	return (NULL);
}

int	is_door_open(t_cub *cub, int x, int y)
{
	t_door	*door;

	door = get_door_at(cub, x, y);
	if (!door)
		return (0);
	return (door->state == DOOR_OPEN
		&& door->frame >= DOOR_FRAMES - 1);
}
