#include "../includes/thedump.h"
#include <math.h>

int	enemy_has_line_of_sight(t_cub *cub, t_enemy *e)
{
	double	dx;
	double	dy;
	double	len;
	double	cx;
	double	cy;
	int		steps;
	int		i;

	dx = cub->player->pos_x - e->x;
	dy = cub->player->pos_y - e->y;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.001)
		return (1);
	dx /= len;
	dy /= len;
	steps = (int)(len / 0.2);
	i = 0;
	cx = e->x;
	cy = e->y;
	while (i < steps)
	{
		cx += dx * 0.2;
		cy += dy * 0.2;
		if (!can_walk(cub, (int)cx, (int)cy) ||
			!can_walk(cub, (int)(cx + 0.1), (int)cy) ||
			!can_walk(cub, (int)(cx - 0.1), (int)cy) ||
			!can_walk(cub, (int)cx, (int)(cy + 0.1)) ||
			!can_walk(cub, (int)cx, (int)(cy - 0.1)))
			return (0);
		i++;
	}
	return (1);
}

void	enemy_ai_idle(t_cub *cub, t_enemy *e)
{
	double	dx;
	double	dy;

	dx = cub->player->pos_x - e->x;
	dy = cub->player->pos_y - e->y;
	e->dist = dx * dx + dy * dy;
	if (e->dist < DETECTION_RADIUS * DETECTION_RADIUS)
	{
		if (enemy_has_line_of_sight(cub, e))
			e->state = EN_CHASE;
	}
}

static void	enemy_move_flow_field(t_cub *cub, t_enemy *e)
{
	int		ex = (int)e->x;
	int		ey = (int)e->y;
	int		best_x = ex;
	int		best_y = ey;
	int		min_dist = 999999;
	int		dx_arr[8] = {0, 0, 1, -1, 1, 1, -1, -1};
	int		dy_arr[8] = {1, -1, 0, 0, 1, -1, 1, -1};
	int		i = 0;
	double	target_x;
	double	target_y;
	double	dx2;
	double	dy2;
	double	len2;
	double	new_x;
	double	new_y;

	if (ex >= 0 && ex < cub->map->width && ey >= 0 && ey < cub->map->height && cub->map->flow_field)
		min_dist = cub->map->flow_field[ey][ex];
	while (i < 8)
	{
		int nx = ex + dx_arr[i];
		int ny = ey + dy_arr[i];
		if (nx >= 0 && nx < cub->map->width && ny >= 0 && ny < cub->map->height && can_walk(cub, nx, ny))
		{
			if (cub->map->flow_field && cub->map->flow_field[ny][nx] < min_dist)
			{
				min_dist = cub->map->flow_field[ny][nx];
				best_x = nx;
				best_y = ny;
			}
		}
		i++;
	}
	if (min_dist < 999999 && (best_x != ex || best_y != ey))
	{
		target_x = best_x + 0.5;
		target_y = best_y + 0.5;
		dx2 = target_x - e->x;
		dy2 = target_y - e->y;
		len2 = sqrt(dx2 * dx2 + dy2 * dy2);
		if (len2 > 0.001)
		{
			dx2 /= len2;
			dy2 /= len2;
			e->dir_x = dx2;
			e->dir_y = dy2;
			new_x = e->x + dx2 * e->speed;
			new_y = e->y + dy2 * e->speed;
			if (can_walk(cub, (int)new_x, (int)e->y))
				e->x = new_x;
			if (can_walk(cub, (int)e->x, (int)new_y))
				e->y = new_y;
		}
	}
	else
		e->state = EN_IDLE;
}

void	enemy_ai_chase(t_cub *cub, t_enemy *e)
{
	double	dx;
	double	dy;
	double	len;
	double	new_x;
	double	new_y;

	dx = cub->player->pos_x - e->x;
	dy = cub->player->pos_y - e->y;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.001)
		return ;
	e->dist = len * len;
	if (!enemy_has_line_of_sight(cub, e))
	{
		enemy_move_flow_field(cub, e);
		return ;
	}
	double	attack_range;
	
	attack_range = (e->type != DOG_TYPE) ? 8.0 : 1.0;
	if (len < attack_range)
	{
		if (e->state != EN_ATTACK && e->type == DOG_TYPE)
			play_dog_attack_sound(cub);
		e->state = EN_ATTACK;
		e->attack_timer = 0;
		return ;
	}
	dx /= len;
	dy /= len;
	e->dir_x = dx;
	e->dir_y = dy;
	new_x = e->x + dx * e->speed;
	new_y = e->y + dy * e->speed;
	if (can_walk(cub, (int)new_x, (int)e->y))
		e->x = new_x;
	if (can_walk(cub, (int)e->x, (int)new_y))
		e->y = new_y;
}

void	enemy_ai_attack(t_cub *cub, t_enemy *e)
{
	double	dx;
	double	dy;
	double	len;
	int		cooldown;

	double	attack_range;

	dx = cub->player->pos_x - e->x;
	dy = cub->player->pos_y - e->y;
	len = sqrt(dx * dx + dy * dy);
	e->dist = len * len;
	
	attack_range = (e->type != DOG_TYPE) ? 8.0 : 1.5;
	if (len > attack_range || !enemy_has_line_of_sight(cub, e))
	{
		e->state = EN_CHASE;
		return ;
	}
	cooldown = ENEMY_ATK_COOLDOWN;
	if (e->is_boss && e->hp < 50)
		cooldown = ENEMY_ATK_COOLDOWN / 2;
	e->attack_timer++;
	if (e->attack_timer >= cooldown)
	{
		int final_damage = e->damage;
		if (cub->difficulty == DIFF_EASY)
			final_damage = e->damage / 2;
		else if (cub->difficulty == DIFF_HARD)
			final_damage = e->damage * 2;
		if (final_damage < 1)
			final_damage = 1;

		if (cub->gold_buff_timer <= 0)
		{
			cub->player_hp -= final_damage;
			if (cub->player_hp < 0)
				cub->player_hp = 0;
		}
		e->attack_timer = 0;
	}
}
