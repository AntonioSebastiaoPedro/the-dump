/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 08:20:00 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 08:20:00 by aamandio         ###   ########.fr       */
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
	{
		cub->door = NULL;
		return ;
	}
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

t_door	*find_door_in_front(t_cub *cub)
{
	double	i;
	int		grid_x;
	int		grid_y;
	t_door	*door;

	i = 0.0;
	while (i < MAX_DOOR_DIST)
	{
		grid_x = (int)(cub->player->pos_x + cub->player->dir_x * i);
		grid_y = (int)(cub->player->pos_y + cub->player->dir_y * i);
		door = get_door_at(cub, grid_x, grid_y);
		if (door)
			return (door);
		i += 0.1;
	}
	return (NULL);
}

void	try_interact_door(t_cub *cub)
{
	t_door	*door;

	door = find_door_in_front(cub);
	if (!door)
		return ;
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
	else if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSING;
}

static void	update_single_door(t_door *door)
{
	door->timer++;
	if (door->timer < FRAME_DELAY)
		return ;
	door->timer = 0;
	if (door->state == DOOR_OPENING)
	{
		door->frame++;
		if (door->frame >= DOOR_FRAMES - 1)
		{
			door->frame = DOOR_FRAMES - 1;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->frame--;
		if (door->frame <= 0)
		{
			door->frame = 0;
			door->state = DOOR_CLOSED;
		}
	}
}

void	update_doors(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->n_door)
	{
		update_single_door(&cub->door[i]);
		i++;
	}
}
