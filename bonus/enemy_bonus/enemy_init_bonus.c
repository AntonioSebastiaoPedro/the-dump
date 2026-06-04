#include "../includes_bonus/cub_bonus.h"

static int	count_enemies(t_cub *cub)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (ft_strchr("MDBO", cub->map->grid[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	set_enemy_stats(t_enemy *e, char type)
{
	if (type == 'B')
	{
		e->is_boss = 1;
		e->type = OFFICER_TYPE;
		e->hp = 100;
		e->damage = 25;
		e->speed = ENEMY_SPEED * 1.2;
	}
	else if (type == 'D')
	{
		e->is_boss = 0;
		e->type = DOG_TYPE;
		e->hp = DOG_HP;
		e->damage = DOG_DAMAGE;
		e->speed = DOG_SPEED;
	}
	else if (type == 'O')
	{
		e->is_boss = 0;
		e->type = OFFICER_TYPE;
		e->hp = OFFICER_HP;
		e->damage = OFFICER_DAMAGE;
		e->speed = OFFICER_SPEED;
	}
	else
	{
		e->is_boss = 0;
		e->type = SOLDIER_TYPE;
		e->hp = ENEMY_HP;
		e->damage = ENEMY_DAMAGE;
		e->speed = ENEMY_SPEED;
	}
}

static void	add_enemy(t_cub *cub, int x, int y, char type)
{
	t_enemy	*e;

	e = &cub->enemies[cub->enemy_count];
	e->x = (double)x + 0.5;
	e->y = (double)y + 0.5;
	e->dir_x = 0.0;
	e->dir_y = 0.0;
	e->dist = 0.0;
	set_enemy_stats(e, type);
	e->alive = 1;
	e->frame = 0;
	e->frame_timer = 0;
	e->attack_timer = 0;
	e->state = EN_IDLE;
	cub->enemy_count++;
}

void	init_enemies(t_cub *cub)
{
	int	total;
	int	y;
	int	x;

	total = count_enemies(cub);
	cub->enemy_count = 0;
	if (total == 0)
	{
		cub->enemies = NULL;
		return ;
	}
	cub->enemies = ft_calloc(total, sizeof(t_enemy));
	if (!cub->enemies)
		return ;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (ft_strchr("MDBO", cub->map->grid[y][x]))
			{
				add_enemy(cub, x, y, cub->map->grid[y][x]);
				cub->map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
