#include "../includes/thedump.h"

static void	draw_tac_pixel(t_cub *cub, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	ft_put_pixel(cub, x, y, color);
}

static void	draw_tac_rect(t_cub *cub, int x, int y, t_vec sz, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)sz.y)
	{
		j = 0;
		while (j < (int)sz.x)
		{
			draw_tac_pixel(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_tac_overlay(t_cub *cub)
{
	int				x;
	int				y;
	unsigned int	*pos;

	pos = (unsigned int *)cub->mlx->addr;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			*(pos + y * WIDTH + x) = (*(pos + y * WIDTH + x) >> 2)
				& 0x3F3F3F3F;
			x++;
		}
		y++;
	}
}

static int	get_grid_color(char tile)
{
	if (tile == '1')
		return (RADAR_WALL);
	if (tile == 'D')
		return (RADAR_DOOR);
	if (tile == '0' || is_player(tile)
		|| tile == 'M' || tile == 'O' || tile == 'B')
		return (RADAR_FLOOR);
	if (tile == 'H' || tile == 'P' || tile == 'K'
		|| tile == 'G' || tile == 'L')
		return (RADAR_FLOOR);
	return (0);
}

static void	draw_tac_grid(t_cub *cub, int ts, int ox, int oy)
{
	int		x;
	int		y;
	int		color;
	t_vec	sz;

	sz.x = ts - 1;
	sz.y = ts - 1;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->map->grid[y]))
		{
			color = get_grid_color(cub->map->grid[y][x]);
			if (color != 0)
				draw_tac_rect(cub, ox + x * ts, oy + y * ts, sz, color);
			x++;
		}
		y++;
	}
}

static int	get_item_color(t_item_type type)
{
	if (type == ITEM_MEDIC_KIT)
		return (GREEN);
	if (type == ITEM_BLUE_KEY)
		return (BLUE);
	if (type == ITEM_BARREL)
		return (MEDIUM_GRAY);
	if (type == ITEM_GOLD_PLANT)
		return (YELLOW);
	if (type == ITEM_WELL)
		return (CYAN);
	return (WHITE);
}

static void	draw_tac_items(t_cub *cub, int ts, int ox, int oy)
{
	int		i;
	int		color;
	t_vec	sz;

	sz.x = ts / 2 + 1;
	sz.y = ts / 2 + 1;
	i = 0;
	while (i < cub->item_count)
	{
		if (cub->items[i].active && cub->items[i].type == ITEM_BLUE_KEY)
		{
			color = get_item_color(cub->items[i].type);
			draw_tac_rect(cub, ox + (int)(cub->items[i].x * ts),
				oy + (int)(cub->items[i].y * ts), sz, color);
		}
		i++;
	}
}

static void	draw_tac_enemies(t_cub *cub, int ts, int ox, int oy)
{
	int		i;
	t_vec	sz;

	sz.x = ts / 2 + 1;
	sz.y = ts / 2 + 1;
	i = 0;
	while (i < cub->enemy_count)
	{
		if (cub->enemies[i].alive)
		{
			if (cub->enemies[i].is_boss)
				draw_tac_rect(cub, ox + (int)(cub->enemies[i].x * ts),
					oy + (int)(cub->enemies[i].y * ts), sz, MAGENTA);
			else
				draw_tac_rect(cub, ox + (int)(cub->enemies[i].x * ts),
					oy + (int)(cub->enemies[i].y * ts), sz, RED);
		}
		i++;
	}
}

static void	draw_tac_player(t_cub *cub, int ts, int ox, int oy)
{
	int		px;
	int		py;
	int		i;
	t_vec	sz;

	px = ox + (int)(cub->player->pos_x * ts);
	py = oy + (int)(cub->player->pos_y * ts);
	sz.x = 5;
	sz.y = 5;
	draw_tac_rect(cub, px - 2, py - 2, sz, RADAR_PLAYER);
	i = 0;
	while (i < ts)
	{
		draw_tac_pixel(cub,
			px + (int)(cub->player->dir_x * i),
			py + (int)(cub->player->dir_y * i), RADAR_DIR);
		i++;
	}
}

void	draw_tactical_map(t_cub *cub)
{
	int		ts;
	int		map_w;
	int		map_h;
	int		ox;
	int		oy;
	t_vec	sz;

	draw_tac_overlay(cub);
	ts = (int)((WIDTH * 0.8) / cub->map->width);
	if ((int)((HEIGHT * 0.8) / cub->map->height) < ts)
		ts = (int)((HEIGHT * 0.8) / cub->map->height);
	if (ts < 1)
		ts = 1;
	map_w = cub->map->width * ts;
	map_h = cub->map->height * ts;
	ox = (WIDTH - map_w) / 2;
	oy = (HEIGHT - map_h) / 2;
	sz.x = map_w + 10;
	sz.y = map_h + 10;
	draw_tac_rect(cub, ox - 5, oy - 5, sz, GRAY);
	sz.x = map_w;
	sz.y = map_h;
	draw_tac_rect(cub, ox, oy, sz, BLACK);
	draw_tac_grid(cub, ts, ox, oy);
	draw_tac_items(cub, ts, ox, oy);
	draw_tac_enemies(cub, ts, ox, oy);
	draw_tac_player(cub, ts, ox, oy);
}
