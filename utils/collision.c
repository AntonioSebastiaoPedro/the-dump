#include "../includes/thedump.h"

int	is_walkable_aabb(t_cub *cub, double new_x, double new_y, double size)
{
	int	x_min;
	int	x_max;
	int	y_min;
	int	y_max;

	x_min = (int)(new_x - size);
	x_max = (int)(new_x + size);
	y_min = (int)(new_y - size);
	y_max = (int)(new_y + size);
	if (!can_walk(cub, x_min, y_min))
		return (0);
	if (!can_walk(cub, x_max, y_min))
		return (0);
	if (!can_walk(cub, x_min, y_max))
		return (0);
	if (!can_walk(cub, x_max, y_max))
		return (0);
	return (1);
}
