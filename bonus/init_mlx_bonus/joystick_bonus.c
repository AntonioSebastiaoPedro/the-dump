/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joystick_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:27:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/04 16:59:16 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"
#include <linux/joystick.h>

void	init_joystick(t_cub *cub)
{
	cub->joy_fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
	if (cub->joy_fd < 0)
		ft_fprintf_fd(2, "Joystick: /dev/input/js0 not found\n");
	ft_memset(cub->joy_axis, 0, sizeof(cub->joy_axis));
}

void	close_joystick(t_cub *cub)
{
	if (cub->joy_fd >= 0)
		close(cub->joy_fd);
	cub->joy_fd = -1;
}


static void	handle_joy_buttons(t_cub *cub, struct js_event *e)
{
	if (e->value != 1)
		return ;
	if (cub->state == MENU)
	{
		if (e->number == 0 || e->number == 2 || e->number == 7)
			handle_menu_input(65293, cub); // enter
		else if (e->number == 1 || e->number == 7)
			handle_menu_input(65307, cub);
		else if (e->number == 11 || e->number == 13) /* UP */
			handle_menu_input(65362, cub);
		else if (e->number == 12 || e->number == 14) /* DOWN */
			handle_menu_input(65364, cub);
	}
	else if (cub->state == ABOUT)
	{
		if (e->number == 0 || e->number == 1 || e->number == 2 || e->number == 7)
			handle_menu_input(65307, cub);
	}
	else if (cub->state == GAME)
	{
		if (e->number == 5)
			on_mouse_click(cub);
		else if (e->number == 1)
			try_interact_door(cub);
		else if (e->number == 3)
			cub->show_mira = !cub->show_mira;
		else if (e->number == 6)
			toggle_mouse_vis(cub);
		else if (e->number == 7)
			cub->state = MENU;
		else if (e->number == 4)
			switch_weapon_next(cub);
	}
	else if (cub->state == LEVEL_TRANSITION)
	{
		if (e->number == 6 || e->number == 7 || e->number == 0)
		{
			load_next_level(cub);
		}
	}
	else if (cub->state == GAME_OVER || cub->state == VICTORY)
	{
		if (e->number == 6 || e->number == 7 || e->number == 0)
		{
			restart_game(cub);
		}
	}
}

static void	handle_joy_axes(t_cub *cub, struct js_event *e)
{
	if (e->number >= 8)
		return ;
	if (cub->state == MENU)
	{
		if (e->number == 1 || e->number == 5 || e->number == 7)
		{
			if (e->value < -JOY_DEADZONE && cub->joy_axis[e->number] >= -JOY_DEADZONE)
			{
				/* UP */
				handle_menu_input(65362, cub);
			}
			else if (e->value > JOY_DEADZONE && cub->joy_axis[e->number] <= JOY_DEADZONE)
			{
				/* DOWN */
				handle_menu_input(65364, cub);
			}
		}
	}
	cub->joy_axis[e->number] = e->value;
}

void	poll_joystick(t_cub *cub)
{
	struct js_event	e;

	if (cub->joy_fd < 0)
		return ;
	while (read(cub->joy_fd, &e, sizeof(e)) > 0)
	{
		e.type &= ~JS_EVENT_INIT;
		if (e.type == JS_EVENT_AXIS)
			handle_joy_axes(cub, &e);
		if (e.type == JS_EVENT_BUTTON)
			handle_joy_buttons(cub, &e);
	}
	if (cub->state == GAME && (cub->joy_axis[3] > JOY_DEADZONE
			|| cub->joy_axis[3] < -JOY_DEADZONE))
		rotate(cub->player, cub->joy_axis[3] * JOY_ROT_SENS);
}
