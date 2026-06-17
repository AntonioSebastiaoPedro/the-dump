#include "../includes/thedump.h"

static int	get_pixel_color(t_texture *tex, int x, int y) //trocar
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

static void	put_pixel_to_tex(t_texture *tex, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return ;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	scale_help(t_texture *tex, int new_w, int new_h, t_texture *new_tex)
{
	int			x;
	int			y;
	int			src_x;
	int			src_y;

	y = 0;
	while (y < new_h)
	{
		x = 0;
		while (x < new_w)
		{
			src_x = x * tex->width / new_w;
			src_y = y * tex->height / new_h;
			put_pixel_to_tex(new_tex, x, y,
				get_pixel_color(tex, src_x, src_y));
			x++;
		}
		y++;
	}
}

int	scale_texture(t_cub *cub, t_texture *tex, int new_w, int new_h)
{
	t_texture	new_tex;

	new_tex.img = mlx_new_image(cub->mlx->mlx, new_w, new_h);
	if (!new_tex.img)
		return (0);
	new_tex.addr = mlx_get_data_addr(new_tex.img, &new_tex.bpp,
			&new_tex.line_len, &new_tex.endian);
	new_tex.width = new_w;
	new_tex.height = new_h;
	scale_help(tex, new_w, new_h, &new_tex);
	return (mlx_destroy_image(cub->mlx->mlx, tex->img), *tex = new_tex, 1);
}