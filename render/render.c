/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/17 02:52:13 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*static void	draw_square_in_map(t_cub *cub, int x, int y, int color)
{
	int	row;
	int	col;

	row = 0;
	while (row < TILE_SIZE)
	{
		col = 0;
		while (col < TILE_SIZE)
		{
			ft_put_pixel(cub, x + col, y + row, color);
			col++;
		}
		row++;
	}
}

static void	draw_map(t_cub *cub)
{
	int	row;
	int	col;

	row = 0;
	while (row < cub->map->height)
	{
		col = 0;
		while (col < cub->map->width)
		{
			if (cub->map->grid[row][col] == '1')
			{
				// draw wall
				draw_square_in_map(cub, col * TILE_SIZE, row * TILE_SIZE, RED);
			}
			else
			{
				// draw empty space
				draw_square_in_map(cub, col * TILE_SIZE, row * TILE_SIZE, YELLOW);
			}
			col++;
		}
		row++;
	}
}*/

void	render(t_cub *cub)
{
	unsigned int	*pos;
	int				x;
	t_ray			ray;

	x = 0;
	pos = (unsigned int *)cub->mlx->addr;
	while (x < WIDTH * HEIGHT)
		*(pos + x++) = BLACK;
	x = 0;
	while (x < WIDTH)
	{
		setup_ray(cub, &ray, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
