#include "../includes_bonus/cub_bonus.h"

void	update_enemy_animation(t_enemy *e)
{
	int	max_frames;

	if (!e->alive && e->state != EN_DEAD)
		return ;
	e->frame_timer++;
	if (e->frame_timer < ENEMY_FRAME_DELAY)
		return ;
	e->frame_timer = 0;
	if (e->state == EN_IDLE)
		max_frames = ENEMY_IDLE_FRAMES;
	else if (e->state == EN_CHASE)
		max_frames = ENEMY_WALK_FRAMES;
	else if (e->state == EN_ATTACK)
		max_frames = ENEMY_ATTACK_FRAMES;
	else if (e->state == EN_HURT)
	{
		e->state = EN_CHASE;
		e->frame = 0;
		return ;
	}
	else if (e->state == EN_DEAD)
	{
		if (e->frame < ENEMY_DEAD_FRAMES - 1)
			e->frame++;
		else
			e->alive = 0;
		return ;
	}
	else
		return ;
	e->frame++;
	if (e->frame >= max_frames)
		e->frame = 0;
}

t_texture	*get_enemy_texture(t_cub *cub, t_enemy *e)
{
	if (e->state == EN_IDLE)
		return (&cub->enemy_anims.idle[e->frame % ENEMY_IDLE_FRAMES]);
	else if (e->state == EN_CHASE)
		return (&cub->enemy_anims.walk[e->frame % ENEMY_WALK_FRAMES]);
	else if (e->state == EN_ATTACK)
		return (&cub->enemy_anims.attack[e->frame % ENEMY_ATTACK_FRAMES]);
	else if (e->state == EN_HURT)
		return (&cub->enemy_anims.idle[0]);
	else if (e->state == EN_DEAD)
		return (&cub->enemy_anims.dead[e->frame % ENEMY_DEAD_FRAMES]);
	return (&cub->enemy_anims.idle[0]);
}
