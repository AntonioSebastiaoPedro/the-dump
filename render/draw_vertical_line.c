#include "../includes/thedump.h"

t_floorceil_args	make_args(int col, int y, int is_floor)
{
	t_floorceil_args	a;

	a.col = col;
	a.y = y;
	a.is_floor = is_floor;
	return (a);
}

void	draw_ceiling(t_cub *cub, t_ray *ray, int *y, int col)
{
	t_floorceil_args	a;
	unsigned int		color;

	while (*y < ray->draw_start)
	{
		a = make_args(col, *y, 0);
		color = get_floor_ceiling_pixel_color(cub, a, ray);
		ft_put_pixel(cub, col, *y, color);
		if (*y + 1 < ray->draw_start)
			ft_put_pixel(cub, col, *y + 1, color);
		*y += 2;
	}
}

void	draw_wall(t_cub *cub, t_ray *ray, int *y, int col)
{
	t_texture			*texture;
	int					tex_y;
	unsigned int		color;

	texture = get_texture(ray, cub);
	while (*y <= ray->draw_end)
	{
		tex_y = (int)ray->texture_pos;
		ray->texture_pos += ray->step_texture;
		color = get_texture_color(texture, ray->texture_column, tex_y);
		if (color != TRANSPARENT_BACKGROUND)
		{
			color = apply_depth_shading(color, ray->perp_wall_dist);
			ft_put_pixel(cub, col, *y, color);
		}
		(*y)++;
	}
}

void	draw_floor(t_cub *cub, t_ray *ray, int *y, int col)
{
	t_floorceil_args	a;
	unsigned int		color;

	while (*y < HEIGHT)
	{
		a = make_args(col, *y, 1);
		color = get_floor_ceiling_pixel_color(cub, a, ray);
		ft_put_pixel(cub, col, *y, color);
		if (*y + 1 < HEIGHT)
			ft_put_pixel(cub, col, *y + 1, color);
		*y += 2;
	}
}

void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int					y;

	y = 0;
	draw_ceiling(cub, ray, &y, col);
	draw_wall(cub, ray, &y, col);
	draw_floor(cub, ray, &y, col);
}