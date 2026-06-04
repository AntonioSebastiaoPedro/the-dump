#include "../includes_bonus/cub_bonus.h"

int	enemy_can_move(t_cub *cub, double x, double y)
{
	return (can_walk(cub, (int)x, (int)y));
}
