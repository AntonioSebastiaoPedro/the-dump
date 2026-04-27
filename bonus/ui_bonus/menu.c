/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:40:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 15:33:06 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	init_menu(t_cub *cub)
{
	cub->menu.selected = 0;
	cub->menu.total = 3;
}

void	update_menu(t_cub *cub)
{
	(void)cub;
}

void	handle_menu_selected(t_cub *cub)
{
	if (cub->menu.selected == 0)
	{
		cub->state = GAME;
		mlx_mouse_hide(cub->mlx->mlx, cub->mlx->win);
		mlx_mouse_move(cub->mlx->mlx, cub->mlx->win,
			cub->mouse.center_x, cub->mouse.center_y);
	}
	else if (cub->menu.selected == 1)
		cub->state = ABOUT;
	else if (cub->menu.selected == 2)
		(free_cub(cub), exit(0));
}

void	handle_menu_input(int key, t_cub *cub)
{
	if (cub->state == MENU)
	{
		if (key == KEY_UP || key == KEY_W)
		{
			cub->menu.selected--;
			if (cub->menu.selected < 0)
				cub->menu.selected = cub->menu.total - 1;
		}
		else if (key == KEY_DOWN || key == KEY_S)
		{
			cub->menu.selected++;
			if (cub->menu.selected >= cub->menu.total)
				cub->menu.selected = 0;
		}
		else if (key == KEY_ENTER)
			handle_menu_selected(cub);
	}
	else if (cub->state == ABOUT)
	{
		if (key == ESC)
			cub->state = MENU;
	}
}
