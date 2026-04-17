/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:48:35 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/17 15:21:48 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

static void	move_forward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (map->grid[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (map->grid[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (map->grid[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (map->grid[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

static void	strafe(t_player *player, t_map *map, int dir)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + dir * player->plane_x * MOVE_SPEED;
	new_y = player->pos_y + dir * player->plane_y * MOVE_SPEED;
	if (map->grid[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (map->grid[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

static void	rotate(t_player *player, double rot)
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
	if (cub->keys[KEY_W])
		move_forward(cub->player, cub->map);
	if (cub->keys[KEY_S])
		move_backward(cub->player, cub->map);
	if (cub->keys[KEY_A])
		strafe(cub->player, cub->map, -1);
	if (cub->keys[KEY_D])
		strafe(cub->player, cub->map, 1);
	if (cub->keys[KEY_LEFT])
		rotate(cub->player, -ROT_SPEED);
	if (cub->keys[KEY_RIGHT])
		rotate(cub->player, ROT_SPEED);
}
