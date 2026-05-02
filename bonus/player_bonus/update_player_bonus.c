/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:48:35 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/02 14:11:16 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	can_move(t_cub *cub, int x, int y)
{
	if (x < 0 || x >= cub->map->width || y < 0 || y >= cub->map->height)
		return (0);
	if (cub->map->grid[y][x] == '0')
		return (1);
	if (cub->map->grid[y][x] == 'D' && is_door_open(cub, x, y))
		return (1);
	return (0);
}

static void	move_forward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (can_move(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_move(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (can_move(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_move(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	strafe(t_player *player, t_cub *cub, int dir)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + dir * player->plane_x * MOVE_SPEED;
	new_y = player->pos_y + dir * player->plane_y * MOVE_SPEED;
	if (can_move(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_move(cub, (int)player->pos_x, (int)new_y))
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
}
