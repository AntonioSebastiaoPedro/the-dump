/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:09:20 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 17:43:51 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	draw_line_dir(t_cub *cub, t_mmap_render *mmap)
{
	int	dx;
	int	dy;

	dx = (int)((cub->player->pos_x + cub->player->dir_x * 0.5) * mmap->scale)
		+ mmap->off_x;
	dy = (int)((cub->player->pos_y + cub->player->dir_y * 0.5) * mmap->scale)
		+ mmap->off_y;
	ft_put_pixel(cub, dx, dy, RED);
}

void	draw_player(t_cub *cub, t_mmap_render *mmap)
{
	int	x;
	int	y;
	int	px;
	int	py;

	px = (int)(cub->player->pos_x * mmap->scale) + mmap->off_x
		- PLAYER_SIZE / 2;
	py = (int)(cub->player->pos_y * mmap->scale) + mmap->off_y
		- PLAYER_SIZE / 2;
	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			ft_put_pixel(cub, px + x, py + y, RED);
			x++;
		}
		y++;
	}
	draw_line_dir(cub, mmap);
}

void	draw_square(t_cub *cub, t_ldg_render *render, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < render->h)
	{
		x = 0;
		while (x < render->w)
		{
			ft_put_pixel(cub, render->x + x, render->y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_grid(t_cub *cub, t_mmap_render *mmap)
{
	int				x;
	int				y;
	t_ldg_render	render;

	y = -1;
	while (cub->map->grid[++y])
	{
		x = -1;
		while (cub->map->grid[y][++x])
		{
			render.x = mmap->off_x + x * mmap->scale;
			render.y = mmap->off_y + y * mmap->scale;
			render.w = (int)mmap->scale;
			render.h = (int)mmap->scale;
			if (cub->map->grid[y][x] == '1')
				draw_square(cub, &render, TRANSP);
			else if (cub->map->grid[y][x] == '0')
				draw_square(cub, &render, GRAY);
			else
				draw_square(cub, &render, BLACK);
		}
	}
}

void	draw_minimap(t_cub *cub)
{
	t_mmap_render	mmap;

	mmap.scale = (double)MNP_MAX_SIZE / cub->map->width;
	if ((double)MNP_MAX_SIZE / cub->map->height < mmap.scale)
		mmap.scale = (double)MNP_MAX_SIZE / cub->map->height;
	mmap.off_x = (MNP_MAX_SIZE - (cub->map->width * mmap.scale))
		/ 2 + MNP_OFFSET;
	mmap.off_y = (MNP_MAX_SIZE - (cub->map->height * mmap.scale))
		/ 2 + MNP_OFFSET;
	draw_grid(cub, &mmap);
	draw_player(cub, &mmap);
}
