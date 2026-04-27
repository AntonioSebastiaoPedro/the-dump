/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:42:32 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 16:25:34 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

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
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key >= 0 && key < 65536)
		cub->keys[key] = 0;
	return (0);
}
