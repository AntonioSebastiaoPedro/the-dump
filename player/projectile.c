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
