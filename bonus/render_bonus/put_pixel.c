#include "../includes_bonus/cub.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= cub->mlx->width || y < 0 || y >= cub->mlx->height)
		return ;
	dst = cub->mlx->addr + (y * cub->mlx->line_len + x * (cub->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
