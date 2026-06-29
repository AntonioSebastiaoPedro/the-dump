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
		if (ty > 0.0 && fabs(tx / ty) < CROSSHAIR_TOLERANCE && ty < best_dist)
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
	// Standard max range is WEAPON_MAX_RANGE. If zoomed in (scale < 1.0), increase range.
	// We use 1.0 / zoom_scale as a range multiplier.
	double max_range = WEAPON_MAX_RANGE * (1.0 / zoom_scale);
	double drop_off_start = WEAPON_DROP_OFF_START * (1.0 / zoom_scale);

	if (dist > drop_off_start && dist < max_range)
		return 1;
	if (dist > max_range)
		return 0;
	
	// Close range damage
	double dmg = (WEAPON_DROP_OFF_START - (dist / (1.0 / zoom_scale))) * (rand() % 3 + 1);
	if (dmg < 1)
		dmg = 1;
	return (int)dmg;
}

void	enemy_take_damage(t_cub *cub)
{
	t_enemy	*e;
	double	dist;

	int		i;
	double	best_barrel_dist = 1e30;
	t_item	*best_barrel = NULL;
	double	sx, sy, inv, tx, ty;

	// Check for barrels in crosshair
	i = 0;
	while (i < cub->item_count)
	{
		if (!cub->items[i].active || cub->items[i].type != ITEM_BARREL)
		{
			i++;
			continue ;
		}
		sx = cub->items[i].x - cub->player->pos_x;
		sy = cub->items[i].y - cub->player->pos_y;
		inv = 1.0 / (cub->player->plane_x * cub->player->dir_y
				- cub->player->dir_x * cub->player->plane_y);
		tx = inv * (cub->player->dir_y * sx - cub->player->dir_x * sy);
		ty = inv * (-cub->player->plane_y * sx + cub->player->plane_x * sy);
		if (ty > 0.0 && fabs(tx / ty) < CROSSHAIR_TOLERANCE && ty < best_barrel_dist)
		{
			best_barrel_dist = ty;
			best_barrel = &cub->items[i];
		}
		i++;
	}

	e = find_closest_enemy_in_crosshair(cub);
	if (best_barrel)
	{
		double barrel_dist_sq = pow(best_barrel->x - cub->player->pos_x, 2) + pow(best_barrel->y - cub->player->pos_y, 2);
		if (!e || barrel_dist_sq < e->dist)
		{
			// Shoot the barrel
			if (best_barrel_dist < WEAPON_MAX_RANGE * (1.0 / cub->crosshair.scale))
				explode_barrel(cub, best_barrel);
			return ;
		}
	}

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

	if (cub->gold_buff_timer > 0)
		dmg *= 3;

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
