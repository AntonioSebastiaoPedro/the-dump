#include "../includes/cub.h"

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

	while (*y < ray->draw_start)
	{
		a = make_args(col, *y, 0);
		draw_floor_ceiling_pixel(cub, a, ray);
		(*y)++;
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
			ft_put_pixel(cub, col, *y, color);
		(*y)++;
	}
}

void	draw_floor(t_cub *cub, t_ray *ray, int *y, int col)
{
	t_floorceil_args	a;

	while (*y < HEIGHT)
	{
		a = make_args(col, *y, 1);
		draw_floor_ceiling_pixel(cub, a, ray);
		(*y)++;
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