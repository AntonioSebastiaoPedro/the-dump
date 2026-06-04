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
	int	t;
	int	d;
	int	f;
	t_enemy_anims *a;

	t = 0;
	while (t < ENEMY_TYPE_COUNT)
	{
		a = &cub->enemy_anims[t];
		d = 0;
		while (d < 8)
		{
			f = 0;
			while (f < 4) // Max frames
			{
				destroy_tex(cub, &a->idle[d][f]);
				destroy_tex(cub, &a->walk[d][f]);
				destroy_tex(cub, &a->attack[d][f]);
				f++;
			}
			d++;
		}
		f = 0;
		while (f < ENEMY_DEAD_FRAMES)
			destroy_tex(cub, &a->dead[f++]);
		t++;
	}
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
