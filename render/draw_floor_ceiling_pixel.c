#include "../includes/thedump.h"

static void	get_tex_size(t_cub *cub, t_floorceil_args a, t_tex_info *t)
{
	if (a.is_floor)
	{
		t->w = cub->textures->floor.width;
		t->h = cub->textures->floor.height;
	}
	else
	{
		t->w = cub->textures->ceiling.width;
		t->h = cub->textures->ceiling.height;
	}
}

static double	get_floorceil_dist(t_floorceil_args a)
{
	if (a.is_floor)
		return ((double)HEIGHT / (2.0 * a.y - HEIGHT));
	return ((double)HEIGHT / (HEIGHT - 2.0 * a.y));
}

static void	get_floorceil_pos(t_cub *cub, t_ray *ray,
				t_floorceil_args a, t_floorceil_ctx *c)
{
	c->dist = get_floorceil_dist(a);
	c->fx = cub->player->pos_x + c->dist * ray->dir_x;
	c->fy = cub->player->pos_y + c->dist * ray->dir_y;
}

static void	get_tex_coords(t_floorceil_ctx c,
				t_tex_info t, int *tx, int *ty)
{
	*tx = ((int)(c.fx * t.w)) % t.w;
	*ty = ((int)(c.fy * t.h)) % t.h;
	if (*tx < 0)
		*tx += t.w;
	if (*ty < 0)
		*ty += t.h;
}

unsigned int	get_floor_ceiling_pixel_color(t_cub *cub,
			t_floorceil_args a, t_ray *ray)
{
	t_tex_info		tex;
	t_floorceil_ctx	ctx;
	int				tx;
	int				ty;

	if (a.is_floor && !cub->config->f_tex)
		return (get_floor_or_ceiling_color(cub, a));
	if (!a.is_floor && !cub->config->c_tex)
		return (get_floor_or_ceiling_color(cub, a));
	get_tex_size(cub, a, &tex);
	get_floorceil_pos(cub, ray, a, &ctx);
	get_tex_coords(ctx, tex, &tx, &ty);
	if (a.is_floor)
		return (apply_depth_shading(get_texture_color(&cub->textures->floor, tx, ty), ctx.dist));
	else
		return (apply_depth_shading(get_texture_color(&cub->textures->ceiling, tx, ty), ctx.dist));
}