#include "../includes_bonus/cub_bonus.h"

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	
	/* ===== CLEANUP THREADING SYSTEM ===== */
	if (cub->raycast_pool)
		cleanup_raycast_pool(cub->raycast_pool);
	if (cub->update_thread)
		cleanup_update_thread(cub->update_thread);
	pthread_mutex_destroy(&cub->render_mutex);
	
	free_config(cub);
	if (cub->map)
	{
		if (cub->map->grid)
			free_map(cub->map->grid, cub->map->height);
		free(cub->map);
	}
	if (cub->door)
		free(cub->door);
	if (cub->player)
		free(cub->player);
	if (cub->textures)
	{
		free_textures(cub);
		free(cub->textures);
	}
	free_enemies(cub);
	free_enemy_textures(cub);
	close_joystick(cub);
	free_audio(cub);
	free_mlx(cub);
	free(cub);
}