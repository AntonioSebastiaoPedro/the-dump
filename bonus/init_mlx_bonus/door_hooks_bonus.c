/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_hooks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:55:04 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/02 03:13:54 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

t_door	*find_door_in_front(t_cub *cub)
{
	int		x;
	int		y;
	double	dist;
	double	step;

	dist = 0.0;
	step = 0.1;
	while (dist <= MAX_DOOR_DIST)
	{
		// verificar se nessa posicao ha porta e retornar a porta em causa...
		x = (int)(cub->player->pos_x + cub->player->dir_x * dist);
		y = (int)(cub->player->pos_y + cub->player->dir_y * dist);
		if (cub->map->grid[y][x] == '1') // Evita abrir porta com parede em frente
			return (NULL);
		if (cub->map->grid[y][x] == 'D')
			return (get_door_at(cub, x, y));
		dist += step;
	}
	return (NULL);
}

void	try_interact_door(t_cub *cub)
{
	t_door	*door;

	door = find_door_in_front(cub);
	if (!door)
		return ;
	if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return ;
	if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSING;
	else if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
}
