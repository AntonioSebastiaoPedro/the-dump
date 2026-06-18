#include "../includes/thedump.h"

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

unsigned int	get_floor_or_ceiling_color(t_cub *cub, t_floorceil_args a)
{
	double dist;

	if (a.is_floor)
	{
		dist = ((double)HEIGHT / (2.0 * a.y - HEIGHT));
		return (apply_depth_shading(cub->config->floor_color, dist));
	}
	else
	{
		dist = ((double)HEIGHT / (HEIGHT - 2.0 * a.y));
		return (apply_depth_shading(cub->config->ceiling_color, dist));
	}
}