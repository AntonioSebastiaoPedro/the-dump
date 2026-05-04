/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 19:18:48 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

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
	draw_mira(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
