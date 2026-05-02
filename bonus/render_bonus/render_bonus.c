/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/02 03:50:07 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	update_single_door(t_door *door)
{
	//if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
	//	return ;
	door->timer++;
	if (door->timer < DOOR_FRAME_DELAY)
		return ;
	door->timer = 0;
	if (door->state == DOOR_OPENING)
	{
		door->frame++;
		if (door->frame >= DOOR_FRAMES)
		{
			door->state = DOOR_OPEN;
			door->frame = DOOR_FRAMES - 1;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->frame--;
		if (door->frame <= 0)
		{
			door->state = DOOR_CLOSED;
			door->frame = 0;
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

void	render(t_cub *cub)
{
	//unsigned int	*pos;
	int				i;
	t_ray			ray;

	//i = 0;
	//pos = (unsigned int *)cub->mlx->addr;
	//while (i < WIDTH * HEIGHT)
	//	*(pos + i++) = BLACK;
	update_weapon(cub);
	update_doors(cub);
	i = 0;
	while (i < WIDTH)
		raycasting(i++, &ray, cub);
	draw_minimap(cub);
	draw_weapon(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
