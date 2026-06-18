#include "../includes/thedump.h"
#include <math.h>
#include <stdlib.h>

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

int	damage_rate(double dist, float zoom_scale)
{
	// Standard max range is 9.0. If zoomed in (scale < 1.0), increase range.
	// We use 1.0 / zoom_scale as a range multiplier.
	double max_range = 9.0 * (1.0 / zoom_scale);
	double drop_off_start = 4.0 * (1.0 / zoom_scale);

	if (dist > drop_off_start && dist < max_range)
		return 1;
	if (dist > max_range)
		return 0;
	
	// Close range damage
	double dmg = (4.0 - (dist / (1.0 / zoom_scale))) * (rand() % 3 + 1);
	if (dmg < 1)
		dmg = 1;
	return (int)dmg;
}

void	enemy_take_damage(t_cub *cub)
{
	t_enemy	*e;
	double	dist;

	e = find_closest_enemy_in_crosshair(cub);
	if (!e)
		return ;
	dist = sqrt((cub->player->pos_x - e->x) * (cub->player->pos_x - e->x)
			+ (cub->player->pos_y - e->y) * (cub->player->pos_y - e->y));
	
	int dmg = damage_rate(dist, cub->crosshair.scale);
	if (cub->difficulty == DIFF_EASY)
		dmg *= 2;
	else if (cub->difficulty == DIFF_HARD)
		dmg /= 2;
	if (dmg < 1)
		dmg = 1;

	e->hp -= dmg;
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
