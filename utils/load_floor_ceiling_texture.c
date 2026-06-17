#include "../includes/thedump.h"

bool	load_floor_ceiling_texture(t_cub *cub)
{
	if (cub->config->f_tex)
	{
		if (!load_single_texture(cub, &cub->textures->floor,
				cub->config->f_tex))
			return (0);
	}
	if (cub->config->c_tex)
	{
		if (!load_single_texture(cub, &cub->textures->ceiling,
				cub->config->c_tex))
			return (0);
	}
	return (1);
}