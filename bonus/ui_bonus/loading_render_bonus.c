/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:02:42 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 18:03:33 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	loading_render(t_cub *game)
{
	char			progress_text[30];
	t_ldg_render	ldg;

	draw_texture_img(game, &game->menu.cover);
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
