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
		loading_render(cub);
		pthread_mutex_lock(&cub->loader.mutex);
		if (cub->loader.done)
		{
			pthread_mutex_unlock(&cub->loader.mutex);
			pthread_join(cub->loader.thread, NULL);
			cub->state = MENU;
			init_menu(cub);
		}
		else
			pthread_mutex_unlock(&cub->loader.mutex);
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
		if (cub->player_hp <= 0)
			cub->state = GAME_OVER;
		else if (check_level_completion(cub))
			cub->state = LEVEL_TRANSITION;
		else if (!is_window_focused(cub))
			cub->state = MENU;
	}
	else if (cub->state == LEVEL_TRANSITION)
	{
		poll_joystick(cub);
		render_transition_screen(cub);
		if (cub->keys[KEY_ENTER])
		{
			cub->keys[KEY_ENTER] = 0;
			load_next_level(cub);
		}
	}
	else if (cub->state == GAME_OVER)
	{
		poll_joystick(cub);
		render_game_over(cub);
		if (cub->keys[ESC])
		{
			cub->keys[ESC] = 0;
			restart_game(cub);
		}
	}
	else if (cub->state == VICTORY)
	{
		poll_joystick(cub);
		render_victory_screen(cub);
		if (cub->keys[KEY_ENTER])
		{
			cub->keys[KEY_ENTER] = 0;
			restart_game(cub);
		}
		else if (cub->keys[ESC])
		{
			cub->keys[ESC] = 0;
			ft_close(cub);
		}
	}
	return (0);
}
