#include "../includes/cub.h"
#include <math.h>

static void	sort_enemies(t_enemy *enemies, int count)
{
	int		i;
	int		j;
	t_enemy	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (enemies[j].dist > enemies[i].dist)
			{
				tmp = enemies[i];
				enemies[i] = enemies[j];
				enemies[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

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

static void	compute_projection(t_cub *cub, t_enemy *e, t_sprite_proj *p)
{
	double	scale;

	scale = 1.0;
	if (e->is_boss)
		scale = 2.0;
	p->sx = e->x - cub->player->pos_x;
	p->sy = e->y - cub->player->pos_y;
	p->inv = 1.0 / (cub->player->plane_x * cub->player->dir_y
			- cub->player->dir_x * cub->player->plane_y);
	p->tx = p->inv * (cub->player->dir_y * p->sx
			- cub->player->dir_x * p->sy);
	p->ty = p->inv * (-cub->player->plane_y * p->sx
			+ cub->player->plane_x * p->sy);
	p->screen_x = (int)((WIDTH / 2) * (1.0 + p->tx / p->ty));
	p->sprite_h = abs((int)(HEIGHT / p->ty)) * scale;
	p->sprite_w = p->sprite_h * 1.5; // Making boss wider might be unneeded if square, let's keep it square or 1.0 proportion
	// Actually original was `p->sprite_w = p->sprite_h;`
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
				ft_put_pixel(cub, stripe, y, color);
		}
		y++;
	}
}

static void	draw_single_enemy(t_cub *cub, t_enemy *e)
{
	t_sprite_proj	p;
	t_texture		*tex;
	int				stripe;

	if (!e->alive && e->state != EN_DEAD)
		return ;
	compute_projection(cub, e, &p);
	if (p.ty <= 0.0)
		return ;
	tex = get_enemy_texture(cub, e);
	if (!tex || !tex->img)
		return ;
	stripe = p.draw_sx;
	while (stripe <= p.draw_ex)
	{
		if (stripe >= 0 && stripe < WIDTH && p.ty < cub->zbuffer[stripe])
			draw_sprite_col(cub, &p, tex, stripe);
		stripe++;
	}
}

void	draw_enemies(t_cub *cub)
{
	int	i;

	if (!cub->enemies || cub->enemy_count == 0)
		return ;
	sort_enemies(cub->enemies, cub->enemy_count);
	i = 0;
	while (i < cub->enemy_count)
	{
		draw_single_enemy(cub, &cub->enemies[i]);
		i++;
	}
}
