/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:09:20 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/17 15:23:43 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	draw_line_dir(t_cub *cub)
{
	int	dx;
	int	dy;

	dx = (int)((cub->player->pos_x + cub->player->dir_x * 0.5) * TILE_SIZE);
	dy = (int)((cub->player->pos_y + cub->player->dir_y * 0.5) * TILE_SIZE);
	put_pixel(cub, dx, dy, RED);
}

void	draw_player(t_cub *cub)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = (int)(cub->player->pos_x * TILE_SIZE) - PLAYER_SIZE / 2;
	py = (int)(cub->player->pos_y * TILE_SIZE) - PLAYER_SIZE / 2;
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			put_pixel(cub, px + x, py + y, RED);
			x++;
		}
		y++;
	}
	draw_line_dir(cub);

}

void	draw_square(t_cub *cub, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			put_pixel(cub, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->map->grid[y])
	{
		x = 0;
		while (cub->map->grid[y][x])
		{
			if (cub->map->grid[y][x] == '1')
				draw_square(cub, x * TILE_SIZE, y * TILE_SIZE, TRANSP);
			else if (cub->map->grid[y][x] == '0')
				draw_square(cub, x * TILE_SIZE, y * TILE_SIZE, GRAY);
			else
				draw_square(cub, x * TILE_SIZE, y * TILE_SIZE, BLACK);
			x++;
		}
		y++;
	}
	draw_player(cub);
}
