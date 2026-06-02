/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joystick_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:27:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/02 18:45:28 by paulcard         ###   ########.fr       */
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
	if (e->number == 2)
		on_mouse_click(cub);
	else if (e->number == 1)
		try_interact_door(cub);
	else if (e->number == 2)
		toggle_mouse_vis(cub);
	else if (e->number == 7)
		ft_close(cub);
	else if (e->number == 3)
		cub->show_mira = !cub->show_mira;
	else if (e->number == 7)
		cub->state = MENU;
}

void	poll_joystick(t_cub *cub)
{
	struct js_event	e;

	if (cub->joy_fd < 0)
		return ;
	while (read(cub->joy_fd, &e, sizeof(e)) > 0)
	{
		e.type &= ~JS_EVENT_INIT;
		if (e.type == JS_EVENT_AXIS && e.number < 8)
			cub->joy_axis[e.number] = e.value;
		if (e.type == JS_EVENT_BUTTON)
			handle_joy_buttons(cub, &e);
	}
	if (cub->joy_axis[3] > JOY_DEADZONE || cub->joy_axis[3] < -JOY_DEADZONE)
		rotate(cub->player, cub->joy_axis[3] * JOY_ROT_SENS);
}
