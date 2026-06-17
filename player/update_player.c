#include "../includes/cub.h"

static void	move_forward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED * cub->delta_time;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED * cub->delta_time;
	if (can_walk(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_walk(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	move_backward(t_player *player, t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED * cub->delta_time;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED * cub->delta_time;
	if (can_walk(cub, (int)new_x, (int)player->pos_y))
		player->pos_x = new_x;
	if (can_walk(cub, (int)player->pos_x, (int)new_y))
		player->pos_y = new_y;
}

static void	strafe(t_player *player, t_cub *cub, int dir)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + dir * player->plane_x * MOVE_SPEED * cub->delta_time;
	new_y = player->pos_y + dir * player->plane_y * MOVE_SPEED * cub->delta_time;
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
		rotate(cub->player, -ROT_SPEED);
	if (cub->keys[KEY_RIGHT])
		rotate(cub->player, ROT_SPEED);
	if (old_x != cub->player->pos_x || old_y != cub->player->pos_y)
		play_run_sound(cub);
	else
		stop_run_sound(cub);
	if (cub->player_hp <= 0 && cub->state == GAME)
	{
		play_player_death_sound(cub);
		cub->state = GAME_OVER;
	}
}