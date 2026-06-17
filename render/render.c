#include "../includes/cub.h"

void	render(t_cub *cub)
{
	unsigned int	*pos;
	int				i;

	i = 0;
	pos = (unsigned int *)cub->mlx->addr;
	
	prof_start();
	if (cub->textures->skybox.img)
		draw_skybox(cub);
	while (i < WIDTH * HEIGHT)
	{
		// Only clear floor area if skybox is active, or clear all if not
		if (cub->textures->skybox.img && i < (WIDTH * HEIGHT) / 2)
		{
			i++;
			continue;
		}
		*(pos + i++) = BLACK;
	}
	prof_end("skybox+clear");

	/* ===== RAYCASTING (parallelizado com threads) ===== */
	prof_start();
	if (cub->raycast_pool)
	{
		// Threads já estão processando continuamente
		// Apenas esperamos a sincronização via barrier
		start_raycast_threads(cub);
		wait_raycast_threads(cub);
	}
	else
	{
		// Fallback single-threaded
		t_ray ray;
		i = 0;
		while (i < WIDTH)
			raycasting(i++, &ray, cub);
	}
	prof_end("raycasting");

	prof_start();
	draw_minimap(cub);
	draw_items(cub);
	draw_enemies(cub);
	prof_end("game_objects");

	prof_start();
	draw_weapon(cub);
	draw_mira(cub);
	draw_hp_hud(cub);
	draw_ammo_hud(cub);
	if (cub->show_full_map)
		draw_tactical_map(cub);
	prof_end("ui_hud");

	prof_start();
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	prof_end("mlx_put_image");
}