#include "../includes/thedump.h"

int	enemy_can_move(t_cub *cub, double x, double y)
{
	return (can_walk(cub, (int)x, (int)y));
}
