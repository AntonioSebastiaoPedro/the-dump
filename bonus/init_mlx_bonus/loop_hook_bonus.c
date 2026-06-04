/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:25:08 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 19:09:10 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	is_window_focused(t_cub *cub)
{
	Window	focused_win;
	t_xvar	*xvar;
	int		revert;

	xvar = (t_xvar *)cub->mlx->mlx;
	XGetInputFocus(xvar->display, &focused_win, &revert);
	return (focused_win == xvar->win_list->window);
}

int	loop_hook(t_cub *cub)
{
	if (cub->state == LOADING)
	{
		update_loading(&cub->loading);
		loading_render(cub);
		if (is_loading_complete(&cub->loading))
		{
			cub->state = MENU;
			init_menu(cub);
		}
	}
	else if (cub->state == MENU)
	{
		poll_joystick(cub);
		update_menu(cub);
		render_menu(cub);
	}
	else if (cub->state == ABOUT)
	{
		poll_joystick(cub);
		render_about(cub);
	}
	else if (cub->state == GAME)
	{
		poll_joystick(cub);
		(update_player(cub), update_doors(cub));
		update_enemies(cub);
		render(cub);
		if (!is_window_focused(cub))
			cub->state = MENU;
	}
	return (0);
}
