#include "../includes/cub.h"



static void	null_duplicates(t_cub *cub, void *img)
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
			while (f < 4)
			{
				if (a->idle[d][f].img == img) a->idle[d][f].img = NULL;
				if (a->walk[d][f].img == img) a->walk[d][f].img = NULL;
				if (a->attack[d][f].img == img) a->attack[d][f].img = NULL;
				f++;
			}
			d++;
		}
		f = 0;
		while (f < ENEMY_DEAD_FRAMES)
		{
			if (a->dead[f].img == img) a->dead[f].img = NULL;
			f++;
		}
		t++;
	}
}

void	free_enemy_textures(t_cub *cub)
{
	int	t;
	int	d;
	int	f;
	void *img;

	t = 0;
	while (t < ENEMY_TYPE_COUNT)
	{
		d = 0;
		while (d < 8)
		{
			f = 0;
			while (f < 4)
			{
				img = cub->enemy_anims[t].idle[d][f].img;
				if (img) (mlx_destroy_image(cub->mlx->mlx, img), null_duplicates(cub, img));
				img = cub->enemy_anims[t].walk[d][f].img;
				if (img) (mlx_destroy_image(cub->mlx->mlx, img), null_duplicates(cub, img));
				img = cub->enemy_anims[t].attack[d][f].img;
				if (img) (mlx_destroy_image(cub->mlx->mlx, img), null_duplicates(cub, img));
				f++;
			}
			d++;
		}
		f = 0;
		while (f < ENEMY_DEAD_FRAMES)
		{
			img = cub->enemy_anims[t].dead[f].img;
			if (img) (mlx_destroy_image(cub->mlx->mlx, img), null_duplicates(cub, img));
			f++;
		}
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
