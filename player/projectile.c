#include "../includes/thedump.h"

void	init_projectiles(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		cub->projectiles[i].active = false;
		i++;
	}
	// To do: Load projectile texture
	// load_single_texture(cub, &cub->projectile_tex, "assets/sprites/plasma.xpm");
}

void	fire_projectile(t_cub *cub, double dir_x, double dir_y, int damage)
{
	int	i;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (!cub->projectiles[i].active)
		{
			cub->projectiles[i].x = cub->player->pos_x;
			cub->projectiles[i].y = cub->player->pos_y;
			cub->projectiles[i].dir_x = dir_x;
			cub->projectiles[i].dir_y = dir_y;
			cub->projectiles[i].damage = damage;
			cub->projectiles[i].active = true;
			return ;
		}
		i++;
	}
}

static void	check_projectile_hit(t_cub *cub, t_projectile *p)
{
	int		i;
	t_enemy	*e;
	double	dist;

	i = 0;
	while (i < cub->enemy_count)
	{
		e = &cub->enemies[i];
		if (e->alive && e->state != EN_DEAD)
		{
			dist = sqrt((p->x - e->x) * (p->x - e->x) + (p->y - e->y) * (p->y - e->y));
			if (dist < PROJECTILE_RADIUS + 0.3)
			{
				e->hp -= p->damage;
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
				p->active = false;
				return ;
			}
		}
		i++;
	}
}

void	update_projectiles(t_cub *cub)
{
	int				i;
	t_projectile	*p;
	double			new_x;
	double			new_y;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		p = &cub->projectiles[i];
		if (p->active)
		{
			new_x = p->x + p->dir_x * PROJECTILE_SPEED * cub->delta_time;
			new_y = p->y + p->dir_y * PROJECTILE_SPEED * cub->delta_time;
			if (!is_walkable_aabb(cub, new_x, new_y, PROJECTILE_RADIUS))
				p->active = false;
			else
			{
				p->x = new_x;
				p->y = new_y;
				check_projectile_hit(cub, p);
			}
		}
		i++;
	}
}
