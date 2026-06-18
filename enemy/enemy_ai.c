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
		if (cub->map->grid[(int)cy][(int)cx] == '1')
			return (0);
		if (cub->map->grid[(int)cy][(int)cx] == 'D'
			&& !is_door_open(cub, (int)cx, (int)cy))
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
		e->state = EN_IDLE;
		return ;
	}
	double	attack_range;
	
	attack_range = (e->type != DOG_TYPE) ? 8.0 : 1.0;
	if (len < attack_range)
	{
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

		cub->player_hp -= final_damage;
		if (cub->player_hp < 0)
			cub->player_hp = 0;
		e->attack_timer = 0;
	}
}
