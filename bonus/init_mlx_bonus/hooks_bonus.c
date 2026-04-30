/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:42:32 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/30 18:49:49 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

#define KEY_SPACE	 32

int	ft_close(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

void	hook_close(t_cub *cub)
{
	mlx_hook(cub->mlx->win, 17, 0, ft_close, cub);
}

static void	toggle_mouse(t_cub *cub)
{
	cub->mouse.show_mouse = !cub->mouse.show_mouse;
	if (cub->mouse.show_mouse)
		mlx_mouse_show(cub->mlx->mlx, cub->mlx->win);
	else
		mlx_mouse_hide(cub->mlx->mlx, cub->mlx->win);
}

static void open_door(t_cub *cub)
{
	(void)cub;
	// double step = 0.1;
	// double i = 0;

	// while (i < MAX_DOOR_DIST)
	// {
	// 	int grid_x = (int)(cub->player->pos_x + cub->player->dir_x * i);
	// 	int grid_y = (int)(cub->player->pos_y + cub->player->dir_y * i);

	// 	i += step;
	// }
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC && cub->state == GAME)
		ft_close(cub);
	if (key == KEY_P && cub->state == GAME)
		toggle_mouse(cub);
	if (cub->state == MENU || cub->state == ABOUT)
		handle_menu_input(key, cub);
	if (key >= 0 && key < 65536)
		cub->keys[key] = 1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		cub->player->is_moving = 1;
	if (key == KEY_SPACE)
		open_door(cub);
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key >= 0 && key < 65536)
		cub->keys[key] = 0;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		cub->player->is_moving = 0;
	return (0);
}
