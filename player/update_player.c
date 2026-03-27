/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:48:35 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 16:41:31 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static void	move_forward(t_player *player, t_map *map)
{
	double new_x;
	double new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (map->grid[(int)player->pos_y][(int)new_x] == '0')
		player->pos_x = new_x;
	if (map->grid[(int)new_y][(int)player->pos_x] == '0')
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_map * map)
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

void	update_player(t_player *player, t_map *map, int  key)
{
	(void)map;
	(void)player;
	if (key == KEY_W)
		move_forward(player, map);
	else if (key == KEY_S)
		move_backward(player, map);
	else if (key == KEY_A)
		strafe(player, map, -1);
	else if (key == KEY_D)
		strafe(player, map, 1);
	else if (key == KEY_LEFT)
		rotate(player, -ROT_SPEED);
	else if (key == KEY_RIGHT)
		rotate(player, ROT_SPEED);
}
