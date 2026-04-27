/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:27:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 17:22:49 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	init_loading(t_loading *loading, void *mlx)
{
	(void)mlx;
	loading->progress = 0;
	loading->max_progress = 100;
	loading->frame_count = 0;
	loading->logo = NULL;
	loading->background = NULL;
}

void	update_loading(t_loading *loading)
{
	if (loading->progress < loading->max_progress)
	{
		loading->frame_count++;
		if (loading->frame_count >= 8)
		{
			loading->progress += 1;
			loading->frame_count = 0;
		}
	}
}

int	is_loading_complete(t_loading *loading)
{
	return (loading->progress >= loading->max_progress);
}

static void	draw_rectangle(t_cub *cub, t_ldg_render *ldg, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < ldg->h)
	{
		j = 0;
		while (j < ldg->w)
		{
			ft_put_pixel(cub, ldg->x + j, ldg->y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_cover(t_cub *game)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*pixel;

	if (!game->menu.cover.img)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = game->menu.cover.addr + (y * game->menu.cover.line_len
					+ x * (game->menu.cover.bpp / 8));
			color = *(unsigned int *)pixel;
			ft_put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	loading_render(t_cub *game)
{
	char			progress_text[30];
	t_ldg_render	ldg;

	draw_cover(game);
	ldg.bar_width = 400;
	ldg.bar_height = 30;
	ldg.filled_width = (game->loading.progress * ldg.bar_width)
		/ game->loading.max_progress;
	ldg.x = (WIDTH - ldg.bar_width) / 2 - 2;
	ldg.y = (HEIGHT - ldg.bar_height) / 2 - 2;
	ldg.w = ldg.bar_width + 4;
	ldg.h = ldg.bar_height + 4;
	draw_rectangle(game, &ldg, WHITE);
	ldg.x += 2;
	ldg.y += 2;
	ldg.w = ldg.bar_width;
	ldg.h = ldg.bar_height;
	draw_rectangle(game, &ldg, GRAY);
	ldg.w = ldg.filled_width;
	draw_rectangle(game, &ldg, DARK_GREEN);
	mlx_put_image_to_window(game->mlx->mlx,
		game->mlx->win, game->mlx->img, 0, 0);
	ft_sprintf(progress_text, "Loading... %d%%", game->loading.progress);
	mlx_string_put(game->mlx->mlx, game->mlx->win, (WIDTH / 2) - 50,
		ldg.y + ldg.bar_height + 40, WHITE, progress_text);
}
