#include "cub.h"

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	free_config(cub);
	if (cub->map)
	{
		if (cub->map->grid)
			free_map(cub->map->grid, cub->map->height);
		free(cub->map);
	}
	if (cub->player)
		free(cub->player);
	if (cub->textures)
	{
		free_textures(cub);
		free(cub->textures);
	}
	free_mlx(cub);
	free(cub);
}