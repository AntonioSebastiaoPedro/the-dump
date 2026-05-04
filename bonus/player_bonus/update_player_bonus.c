/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:48:35 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 19:10:21 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static void	move_forward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (can_walk(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_walk(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (can_walk(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_walk(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	strafe(t_player *player, t_cub *cub, int dir)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + dir * player->plane_x * MOVE_SPEED;
	new_y = player->pos_y + dir * player->plane_y * MOVE_SPEED;
	if (can_walk(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_walk(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

void	rotate(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

void	update_player(t_cub *cub)
{
	double	old_x;
	double	old_y;

	old_x = cub->player->pos_x;
	old_y = cub->player->pos_y;
	update_mouse(cub);
	if (cub->keys[KEY_W])
		move_forward(cub->player, cub);
	if (cub->keys[KEY_S])
		move_backward(cub->player, cub);
	if (cub->keys[KEY_A])
		strafe(cub->player, cub, -1);
	if (cub->keys[KEY_D])
		strafe(cub->player, cub, 1);
	if (cub->keys[KEY_LEFT])
		rotate(cub->player, -ROT_SPEED);
	if (cub->keys[KEY_RIGHT])
		rotate(cub->player, ROT_SPEED);
	if (old_x != cub->player->pos_x || old_y != cub->player->pos_y)
		play_run_sound(cub);
	else
		stop_run_sound(cub);
}
