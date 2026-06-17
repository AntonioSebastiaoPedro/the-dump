#include "../includes/thedump.h"

t_player	*init_player(t_cub *cub)
{
	if (!cub->player || !cub->player->dir)
		return (NULL);
	cub->player->is_moving = 0;
	set_dir_vectors(cub->player);
	srand(time(NULL));
	return (cub->player);
}