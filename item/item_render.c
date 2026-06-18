#include "../includes/thedump.h"
#include <math.h>

typedef struct s_sprite_proj
{
	double	sx;
	double	sy;
	double	inv;
	double	tx;
	double	ty;
	int		screen_x;
	int		sprite_h;
	int		sprite_w;
	int		draw_sx;
	int		draw_ex;
	int		draw_sy;
	int		draw_ey;
}	t_sprite_proj;

static void	sort_items(t_item *items, int count)
{
	int		i;
	int		j;
	t_item	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (items[j].dist > items[i].dist)
			{
				tmp = items[i];
				items[i] = items[j];
				items[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	compute_projection(t_cub *cub, t_item *item, t_sprite_proj *p)
{
	p->sx = item->x - cub->player->pos_x;
	p->sy = item->y - cub->player->pos_y;
	p->inv = 1.0 / (cub->player->plane_x * cub->player->dir_y
			- cub->player->dir_x * cub->player->plane_y);
	p->tx = p->inv * (cub->player->dir_y * p->sx
			- cub->player->dir_x * p->sy);
	p->ty = p->inv * (-cub->player->plane_y * p->sx
			+ cub->player->plane_x * p->sy);
	p->screen_x = (int)((WIDTH / 2) * (1.0 + p->tx / p->ty));
	p->sprite_h = abs((int)(HEIGHT / p->ty));
	p->sprite_w = p->sprite_h;
	p->draw_sy = -p->sprite_h / 2 + HEIGHT / 2;
	if (p->draw_sy < 0)
		p->draw_sy = 0;
	p->draw_ey = p->sprite_h / 2 + HEIGHT / 2;
	if (p->draw_ey >= HEIGHT)
		p->draw_ey = HEIGHT - 1;
	p->draw_sx = -p->sprite_w / 2 + p->screen_x;
	if (p->draw_sx < 0)
		p->draw_sx = 0;
	p->draw_ex = p->sprite_w / 2 + p->screen_x;
	if (p->draw_ex >= WIDTH)
		p->draw_ex = WIDTH - 1;
}

static void	draw_sprite_col(t_cub *cub, t_sprite_proj *p, t_texture *tex,
		int stripe)
{
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	tex_x = (int)((stripe - (-p->sprite_w / 2 + p->screen_x))
			* tex->width / p->sprite_w);
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = p->draw_sy;
	while (y <= p->draw_ey)
	{
		tex_y = (y - (-p->sprite_h / 2 + HEIGHT / 2))
			* tex->height / p->sprite_h;
		if (tex_y >= 0 && tex_y < tex->height)
		{
			color = get_texture_color(tex, tex_x, tex_y);
			if (color != TRANSPARENT_BACKGROUND && (color & 0xFF000000) == 0)
			{
				color = apply_depth_shading(color, p->ty);
				ft_put_pixel(cub, stripe, y, color);
			}
		}
		y++;
	}
}

void	draw_items(t_cub *cub)
{
	int				i;
	int				stripe;
	t_sprite_proj	p;
	t_texture		*tex;

	if (cub->item_count == 0)
		return ;
	sort_items(cub->items, cub->item_count);
	i = 0;
	while (i < cub->item_count)
	{
		if (!cub->items[i].active)
		{
			i++;
			continue ;
		}
		compute_projection(cub, &cub->items[i], &p);
		if (p.ty <= 0.1)
		{
			i++;
			continue ;
		}
		tex = &cub->item_textures[cub->items[i].type];
		stripe = p.draw_sx;
		while (stripe <= p.draw_ex)
		{
			if (stripe >= 0 && stripe < WIDTH && p.ty < cub->zbuffer[stripe])
				draw_sprite_col(cub, &p, tex, stripe);
			stripe++;
		}
		i++;
	}
}
