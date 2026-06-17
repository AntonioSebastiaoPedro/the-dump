#include "../includes/thedump.h"

void	update_enemy_animation(t_enemy *e)
{
	int	max_frames;

	if (!e->alive && e->state != EN_DEAD)
		return ;
	e->frame_timer++;
	if (e->frame_timer < ENEMY_FRAME_DELAY)
		return ;
	e->frame_timer = 0;
	max_frames = 1;
	if (e->state == EN_IDLE)
		max_frames = 1;
	else if (e->state == EN_CHASE)
		max_frames = ENEMY_WALK_FRAMES;
	else if (e->state == EN_ATTACK)
	{
		max_frames = ENEMY_ATTACK_FRAMES;
		if (e->type == DOG_TYPE) max_frames = 3;
		else if (e->type == OFFICER_TYPE) max_frames = 2;
	}
	else if (e->state == EN_DEAD)
	{
		max_frames = ENEMY_DEAD_FRAMES;
		if (e->type == DOG_TYPE) max_frames = 3;
		if (e->frame < max_frames - 1)
			e->frame++;
		else
			e->alive = 0;
		return ;
	}
	else if (e->state == EN_HURT)
	{
		e->state = EN_CHASE;
		e->frame = 0;
		return ;
	}
	e->frame++;
	if (e->frame >= max_frames)
		e->frame = 0;
}

static int	get_enemy_dir(t_cub *cub, t_enemy *e)
{
	double	angle;
	double	player_angle;
	double	relative_angle;

	if (e->dir_x == 0 && e->dir_y == 0)
		return (DIR_FRONT);
	player_angle = atan2(cub->player->pos_y - e->y, cub->player->pos_x - e->x);
	angle = atan2(e->dir_y, e->dir_x);
	relative_angle = player_angle - angle;
	while (relative_angle < 0) relative_angle += 2 * M_PI;
	while (relative_angle >= 2 * M_PI) relative_angle -= 2 * M_PI;
	
	if (relative_angle < M_PI / 8 || relative_angle >= 15 * M_PI / 8) return (DIR_FRONT);
	if (relative_angle < 3 * M_PI / 8) return (DIR_FRONT_LEFT);
	if (relative_angle < 5 * M_PI / 8) return (DIR_LEFT);
	if (relative_angle < 7 * M_PI / 8) return (DIR_BACK_LEFT);
	if (relative_angle < 9 * M_PI / 8) return (DIR_BACK);
	if (relative_angle < 11 * M_PI / 8) return (DIR_BACK_RIGHT);
	if (relative_angle < 13 * M_PI / 8) return (DIR_RIGHT);
	return (DIR_FRONT_RIGHT);
}

static t_texture *check_tex(t_texture *tex, t_texture *fallback)
{
	if (!tex || !tex->img)
		return (fallback);
	return (tex);
}

t_texture	*get_enemy_texture(t_cub *cub, t_enemy *e)
{
	int				dir;
	t_enemy_anims	*a;
	t_texture		*tex;

	a = &cub->enemy_anims[e->type];
	dir = get_enemy_dir(cub, e);
	if (e->state == EN_IDLE)
		tex = &a->idle[dir][0];
	else if (e->state == EN_CHASE)
		tex = &a->walk[dir][e->frame % ENEMY_WALK_FRAMES];
	else if (e->state == EN_ATTACK)
		tex = &a->attack[dir][e->frame % ENEMY_ATTACK_FRAMES];
	else if (e->state == EN_DEAD)
		return (&a->dead[e->frame % ENEMY_DEAD_FRAMES]);
	else
		return (&a->idle[0][0]);
	
	// Fallback to front direction if side/back is missing
	if (!tex || !tex->img)
	{
		if (e->state == EN_IDLE) tex = &a->idle[DIR_FRONT][0];
		else if (e->state == EN_CHASE) tex = &a->walk[DIR_FRONT][e->frame % ENEMY_WALK_FRAMES];
		else if (e->state == EN_ATTACK) tex = &a->attack[DIR_FRONT][e->frame % ENEMY_ATTACK_FRAMES];
	}
	return (check_tex(tex, &a->idle[0][0]));
}
