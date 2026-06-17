#include "../includes/cub.h"

void	ft_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*new_addr;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	new_addr = cub->mlx->addr + (y * cub->mlx->line_len)
		+ (x * (cub->mlx->bpp / 8));
	*(unsigned int *)new_addr = color;
}