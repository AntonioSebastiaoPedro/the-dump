#include "../includes/cub.h"

t_player	*init_player(t_cub *cub)
{
	if (!cub->player || !cub->player->dir)
		return (NULL);
	set_dir_vectors(cub->player);
	return (cub->player);
}