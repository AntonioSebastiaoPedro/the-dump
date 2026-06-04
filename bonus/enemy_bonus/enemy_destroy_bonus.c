#include "../includes_bonus/cub_bonus.h"

static void	destroy_tex(t_cub *cub, t_texture *tex)
{
	if (tex->img)
	{
		mlx_destroy_image(cub->mlx->mlx, tex->img);
		tex->img = NULL;
	}
}

void	free_enemy_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < ENEMY_IDLE_FRAMES)
		destroy_tex(cub, &cub->enemy_anims.idle[i++]);
	i = 0;
	while (i < ENEMY_WALK_FRAMES)
		destroy_tex(cub, &cub->enemy_anims.walk[i++]);
	i = 0;
	while (i < ENEMY_ATTACK_FRAMES)
		destroy_tex(cub, &cub->enemy_anims.attack[i++]);
	i = 0;
	while (i < ENEMY_DEAD_FRAMES)
		destroy_tex(cub, &cub->enemy_anims.dead[i++]);
}

void	free_enemies(t_cub *cub)
{
	if (cub->enemies)
	{
		free(cub->enemies);
		cub->enemies = NULL;
	}
	cub->enemy_count = 0;
}
