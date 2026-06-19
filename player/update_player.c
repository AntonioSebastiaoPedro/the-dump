#include "../includes/thedump.h"

static void	move_forward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	speed_mult;

	speed_mult = (cub->gold_buff_timer > 0) ? 2.0 : 1.0;
	new_x = player->pos_x + player->dir_x * MOVE_SPEED * speed_mult * cub->delta_time;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED * speed_mult * cub->delta_time;
	if (is_walkable_aabb(cub, new_x, player->pos_y, 0.2))
		player->pos_x = new_x;
	if (is_walkable_aabb(cub, player->pos_x, new_y, 0.2))
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;
	double	speed_mult;

	speed_mult = (cub->gold_buff_timer > 0) ? 2.0 : 1.0;
	new_x = player->pos_x - player->dir_x * MOVE_SPEED * speed_mult * cub->delta_time;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED * speed_mult * cub->delta_time;
	if (is_walkable_aabb(cub, new_x, player->pos_y, 0.2))
		player->pos_x = new_x;
	if (is_walkable_aabb(cub, player->pos_x, new_y, 0.2))
		player->pos_y = new_y;
}

static void	strafe(t_player *player, t_cub *cub, int dir)
{
	double	new_x;
	double	new_y;
	double	speed_mult;

	speed_mult = (cub->gold_buff_timer > 0) ? 2.0 : 1.0;
	new_x = player->pos_x + dir * player->plane_x * MOVE_SPEED * speed_mult * cub->delta_time;
	new_y = player->pos_y + dir * player->plane_y * MOVE_SPEED * speed_mult * cub->delta_time;
	if (is_walkable_aabb(cub, new_x, player->pos_y, 0.2))
		player->pos_x = new_x;
	if (is_walkable_aabb(cub, player->pos_x, new_y, 0.2))
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

	if (cub->gold_buff_timer > 0)
	{
		cub->gold_buff_timer -= cub->delta_time;
		if (cub->gold_buff_timer < 0)
			cub->gold_buff_timer = 0;
	}

	old_x = cub->player->pos_x;
	old_y = cub->player->pos_y;
	update_mouse(cub);
	if (cub->keys[KEY_W] || (cub->joy_fd >= 0 && (cub->joy_axis[1] < -JOY_DEADZONE
				|| cub->joy_axis[7] < -JOY_DEADZONE)))
		move_forward(cub->player, cub);
	if (cub->keys[KEY_S] || (cub->joy_fd >= 0 && (cub->joy_axis[1] > JOY_DEADZONE
				|| cub->joy_axis[7] > JOY_DEADZONE)))
		move_backward(cub->player, cub);
	if (cub->keys[KEY_A] || (cub->joy_fd >= 0 && (cub->joy_axis[0] < -JOY_DEADZONE
				|| cub->joy_axis[6] < -JOY_DEADZONE)))
		strafe(cub->player, cub, -1);
	if (cub->keys[KEY_D] || (cub->joy_fd >= 0 && (cub->joy_axis[0] > JOY_DEADZONE
				|| cub->joy_axis[6] > JOY_DEADZONE)))
		strafe(cub->player, cub, 1);
	if (cub->keys[KEY_LEFT])
		rotate(cub->player, -ROT_SPEED * cub->delta_time * 60.0);
	if (cub->keys[KEY_RIGHT])
		rotate(cub->player, ROT_SPEED * cub->delta_time * 60.0);
	if (old_x != cub->player->pos_x || old_y != cub->player->pos_y)
		play_run_sound(cub);
	else
		stop_run_sound(cub);
}