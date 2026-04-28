/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:42:32 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/28 12:21:40 by aamandio         ###   ########.fr       */
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

static void	on_mouse_click(t_cub *cub)
{
	if (cub->weapon.state == WEAPON_SHOT)
		return ;
	set_weapon_state(&cub->weapon, WEAPON_SHOT);
}

int	mouse_hook(int key, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (key == 1 && cub->mouse.show_mouse == false)
		on_mouse_click(cub);
	return (0);
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
	if (key == KEY_W || key == KEY_S)
		cub->player->is_moving = 1;
	else
		cub->player->is_moving = 0;
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key >= 0 && key < 65536)
		cub->keys[key] = 0;
	if (key == KEY_W || key == KEY_S)
		cub->player->is_moving = 0;
	return (0);
}

int	loop_hook(t_cub *cub)
{
	if (cub->state == MENU)
	{
		update_menu(cub);
		render_menu(cub);
	}
	else if (cub->state == ABOUT)
		render_about(cub);
	else if (cub->state == GAME)
	{
		update_player(cub);
		render(cub);
	}
	return (0);
}
