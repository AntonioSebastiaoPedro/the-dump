#include "../includes/cub.h"

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(texture->addr + (y * texture->line_len)
			+ (x * (texture->bpp / 8)));
	return (color);
}

void	put_fc_color(t_cub *cub, int col, int y, int is_floor)
{
	if (is_floor)
		ft_put_pixel(cub, col, y, cub->config->floor_color);
	else
		ft_put_pixel(cub, col, y, cub->config->ceiling_color);
}

void	put_floor_or_ceiling(t_cub *cub, t_floorceil_args a)
{
	if (a.is_floor)
		put_fc_color(cub, a.col, a.y, 1);
	else
		put_fc_color(cub, a.col, a.y, 0);
}