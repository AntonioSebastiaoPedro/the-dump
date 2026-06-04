#include "../includes_bonus/cub_bonus.h"
#include <math.h>

static void	update_single_enemy(t_cub *cub, t_enemy *e)
{
	double	dx;
	double	dy;

	if (!e->alive)
		return ;
	dx = cub->player->pos_x - e->x;
	dy = cub->player->pos_y - e->y;
	e->dist = dx * dx + dy * dy;
	if (e->hp <= 0 && e->state != EN_DEAD)
	{
		e->state = EN_DEAD;
		e->frame = 0;
		e->frame_timer = 0;
		play_enemy_death_sound(cub);
	}
	if (e->state == EN_IDLE)
		enemy_ai_idle(cub, e);
	else if (e->state == EN_CHASE)
		enemy_ai_chase(cub, e);
	else if (e->state == EN_ATTACK)
		enemy_ai_attack(cub, e);
	update_enemy_animation(e);
}

void	update_enemies(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->enemy_count)
	{
		update_single_enemy(cub, &cub->enemies[i]);
		i++;
	}
}
