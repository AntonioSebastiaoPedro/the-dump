/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:00:54 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 19:11:19 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static void	draw_button(t_cub *cub, int y, int index, char *label)
{
	int	color;

	if (cub->menu.selected == index)
	{
		color = GREEN;
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			WIDTH / 2 - 30, y, color, label);
	}
	else
	{
		color = WHITE;
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			WIDTH / 2 - 30, y, color, label + 2);
	}
}

void	switch_button(t_cub *cub)
{
	int	y;

	y = HEIGHT / 2 + 20;
	draw_button(cub, y, 0, "> PLAY");
	y += 40;
	draw_button(cub, y, 1, "> ABOUT");
	y += 40;
	draw_button(cub, y, 2, "> QUIT");
}

void	render_menu(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ft_put_pixel(cub, i, j, BG_COLOR);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	if (cub->menu.cover.img)
		mlx_put_image_to_window(cub->mlx->mlx,
			cub->mlx->win, cub->menu.cover.img, 0, 0);
	switch_button(cub);
}
