#include "../includes_bonus/cub_bonus.h"
#include <math.h>

static t_enemy	*find_closest_enemy_in_crosshair(t_cub *cub)
{
	int		i;
	double	best_dist;
	t_enemy	*best;
	double	sx;
	double	sy;
	double	inv;
	double	tx;
	double	ty;

	best = NULL;
	best_dist = 1e30;
	i = 0;
	while (i < cub->enemy_count)
	{
		if (!cub->enemies[i].alive || cub->enemies[i].state == EN_DEAD)
		{
			i++;
			continue ;
		}
		sx = cub->enemies[i].x - cub->player->pos_x;
		sy = cub->enemies[i].y - cub->player->pos_y;
		inv = 1.0 / (cub->player->plane_x * cub->player->dir_y
				- cub->player->dir_x * cub->player->plane_y);
		tx = inv * (cub->player->dir_y * sx - cub->player->dir_x * sy);
		ty = inv * (-cub->player->plane_y * sx + cub->player->plane_x * sy);
		if (ty > 0.0 && fabs(tx / ty) < 0.3 && ty < best_dist)
		{
			if (enemy_has_line_of_sight(cub, &cub->enemies[i]))
			{
				best_dist = ty;
				best = &cub->enemies[i];
			}
		}
		i++;
	}
	return (best);
}

void	enemy_take_damage(t_cub *cub)
{
	t_enemy	*e;

	e = find_closest_enemy_in_crosshair(cub);
	if (!e)
		return ;
	e->hp -= 1;
	if (e->hp <= 0)
	{
		e->state = EN_DEAD;
		e->frame = 0;
		e->frame_timer = 0;
	}
	else
	{
		e->state = EN_HURT;
		e->frame_timer = 0;
	}
}
