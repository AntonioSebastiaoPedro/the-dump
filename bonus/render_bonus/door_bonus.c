/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 08:20:00 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 19:17:45 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

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
	{
		door->state = DOOR_OPENING;
		play_door_sound(cub);
	}
	else if (door->state == DOOR_OPEN)
	{
		if ((int)cub->player->pos_x == door->x
			&& (int)cub->player->pos_y == door->y)
			return ;
		door->state = DOOR_CLOSING;
		play_door_sound(cub);
	}
}

static void	update_single_door(t_door *door)
{
	door->timer++;
	if (door->timer < DOOR_FRAME_DELAY)
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

int	can_walk(t_cub *cub, int x, int y)
{
	char	c;

	if (x < 0 || x >= cub->map->width || y < 0 || y >= cub->map->height)
		return (0);
	c = cub->map->grid[y][x];
	if (c == '0' || c == 'A' || ft_strchr("NSEWMBROG", c))
		return (1);
	if (c == 'D' && is_door_open(cub, x, y))
		return (1);
	return (0);
}
