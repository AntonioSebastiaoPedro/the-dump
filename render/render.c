#include "cub.h"

void	render(t_cub *cub)
{
	unsigned int	*pos;
	int				i;
	t_ray			ray;

	i = 0;
	pos = (unsigned int *)cub->mlx->addr;
	while (i < WIDTH * HEIGHT)
		*(pos + i++) = BLACK;
	i = 0;
	while (i < WIDTH)
		raycasting(i++, &ray, cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}