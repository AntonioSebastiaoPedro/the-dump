#include "../includes/cub.h"
#include <math.h>

/*
** Verifica que todos os ponteiros criticos estao validos.
*/
static int	radar_is_valid(t_cub *cub)
{
	if (!cub || !cub->map || !cub->map->grid)
		return (0);
	if (cub->map->width <= 0 || cub->map->height <= 0)
		return (0);
	return (1);
}

/*
** Acesso seguro ao tile do mapa.
*/
static int	get_radar_tile(t_cub *cub, int mx, int my)
{
	if (my < 0 || my >= cub->map->height)
		return (-1);
	if (!cub->map->grid[my])
		return (-1);
	if (mx < 0 || mx >= (int)ft_strlen(cub->map->grid[my]))
		return (-1);
	return (cub->map->grid[my][mx]);
}

/*
** Determina a cor do tile.
*/
static int	get_tile_color(int tile)
{
	if (tile == '1')
		return (RADAR_WALL);
	if (tile == 'D')
		return (RADAR_DOOR);
	if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W'
		|| tile == 'M' || tile == 'O' || tile == 'B')
		return (RADAR_FLOOR);
	return (RADAR_BG);
}

/*
** Desenha um pixel apenas dentro do circulo do radar.
*/
void	draw_radar_pixel(t_cub *cub, int x, int y, int color)
{
	int	dx;
	int	dy;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dx = x - RADAR_CENTER_X;
	dy = y - RADAR_CENTER_Y;
	if ((dx * dx + dy * dy) > (RADAR_RADIUS * RADAR_RADIUS))
		return ;
	ft_put_pixel(cub, x, y, color);
}

/*
** Preenche um quadrado de tiles dentro do circulo.
*/
static void	draw_radar_square(t_cub *cub, int sx, int sy, int size, int color)
{
	int	x;
	int	y;

	if (size <= 0)
		return ;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			draw_radar_pixel(cub, sx + x, sy + y, color);
			x++;
		}
		y++;
	}
}

/*
** Fundo circular escuro antes dos tiles.
*/
static void	draw_radar_background(t_cub *cub)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = RADAR_CENTER_Y - RADAR_RADIUS;
	while (y <= RADAR_CENTER_Y + RADAR_RADIUS)
	{
		x = RADAR_CENTER_X - RADAR_RADIUS;
		while (x <= RADAR_CENTER_X + RADAR_RADIUS)
		{
			dx = x - RADAR_CENTER_X;
			dy = y - RADAR_CENTER_Y;
			if ((dx * dx + dy * dy) <= (RADAR_RADIUS * RADAR_RADIUS))
			{
				if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
					ft_put_pixel(cub, x, y, RADAR_BG);
			}
			x++;
		}
		y++;
	}
}

/*
** Desenha os tiles visiveis dentro do raio do radar.
*/
static void	draw_radar_tiles(t_cub *cub, int start_x, int start_y)
{
	int	map_x;
	int	map_y;
	int	tiles;
	int	screen_x;
	int	screen_y;
	int	tile;

	tiles = (RADAR_RADIUS * 2) / RADAR_SCALE + 1;
	map_y = 0;
	while (map_y < tiles)
	{
		map_x = 0;
		while (map_x < tiles)
		{
			screen_x = RADAR_CENTER_X - RADAR_RADIUS + (map_x * RADAR_SCALE);
			screen_y = RADAR_CENTER_Y - RADAR_RADIUS + (map_y * RADAR_SCALE);
			tile = get_radar_tile(cub, start_x + map_x, start_y + map_y);
			draw_radar_square(cub, screen_x, screen_y, RADAR_SCALE,
				get_tile_color(tile));
			map_x++;
		}
		map_y++;
	}
}

/*
** Desenha as linhas de crosshair no centro do radar.
*/
static void	draw_radar_crosshair(t_cub *cub)
{
	int	i;

	i = -RADAR_RADIUS;
	while (i <= RADAR_RADIUS)
	{
		draw_radar_pixel(cub, RADAR_CENTER_X + i, RADAR_CENTER_Y, RADAR_CROSS);
		draw_radar_pixel(cub, RADAR_CENTER_X, RADAR_CENTER_Y + i, RADAR_CROSS);
		i++;
	}
}

/*
** Desenha os circulos concentricos de referencia (estilo sonar).
*/
static void	draw_radar_rings(t_cub *cub)
{
	double	angle;
	int		r;
	int		rx;
	int		ry;

	r = RADAR_RADIUS / 3;
	while (r < RADAR_RADIUS)
	{
		angle = 0.0;
		while (angle < 6.2832)
		{
			rx = RADAR_CENTER_X + (int)(r * cos(angle));
			ry = RADAR_CENTER_Y + (int)(r * sin(angle));
			draw_radar_pixel(cub, rx, ry, RADAR_CROSS);
			angle += 0.01;
		}
		r += RADAR_RADIUS / 3;
	}
}

/*
** Desenha a linha de direcao do jogador a partir do centro.
*/
static void	draw_radar_direction(t_cub *cub)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	while (i < RADAR_DIR_LEN)
	{
		px = RADAR_CENTER_X + (int)(cub->player->dir_x * i);
		py = RADAR_CENTER_Y + (int)(cub->player->dir_y * i);
		draw_radar_pixel(cub, px, py, RADAR_DIR);
		i++;
	}
}

/*
** Desenha o ponto do jogador no centro do radar.
*/
static void	draw_radar_player(t_cub *cub)
{
	int	px;
	int	py;

	px = RADAR_CENTER_X - RADAR_PLAYER_SIZE / 2;
	py = RADAR_CENTER_Y - RADAR_PLAYER_SIZE / 2;
	draw_radar_square(cub, px, py, RADAR_PLAYER_SIZE, RADAR_PLAYER);
	draw_radar_direction(cub);
}

/*
** Desenha a borda circular do radar com dois aneis.
*/
static void	draw_radar_border(t_cub *cub)
{
	double	angle;
	int		bx;
	int		by;

	angle = 0.0;
	while (angle < 6.2832)
	{
		bx = RADAR_CENTER_X + (int)((RADAR_RADIUS) * cos(angle));
		by = RADAR_CENTER_Y + (int)((RADAR_RADIUS) * sin(angle));
		if (bx >= 0 && by >= 0 && bx < WIDTH && by < HEIGHT)
			ft_put_pixel(cub, bx, by, RADAR_BORDER);
		bx = RADAR_CENTER_X + (int)((RADAR_RADIUS - 1) * cos(angle));
		by = RADAR_CENTER_Y + (int)((RADAR_RADIUS - 1) * sin(angle));
		if (bx >= 0 && by >= 0 && bx < WIDTH && by < HEIGHT)
			ft_put_pixel(cub, bx, by, RADAR_BORDER_DIM);
		angle += 0.005;
	}
}

/*
** Desenha as entidades (inimigos) no radar.
*/
static void	draw_radar_enemies(t_cub *cub)
{
	int		i;
	int		ex;
	int		ey;
	double	rel_x;
	double	rel_y;

	i = 0;
	while (i < cub->enemy_count)
	{
		if (cub->enemies[i].alive)
		{
			rel_x = cub->enemies[i].x - cub->player->pos_x;
			rel_y = cub->enemies[i].y - cub->player->pos_y;
			ex = RADAR_CENTER_X + (int)(rel_x * RADAR_SCALE);
			ey = RADAR_CENTER_Y + (int)(rel_y * RADAR_SCALE);
			draw_radar_square(cub, ex - 2, ey - 2, 4, RED);
		}
		i++;
	}
}

/*
** Ponto de entrada do minimapa radar.
** Ordem: fundo -> tiles -> crosshair -> aneis -> inimigos -> jogador -> borda
*/
void	draw_minimap(t_cub *cub)
{
	int	player_map_x;
	int	player_map_y;
	int	start_x;
	int	start_y;
	int	tiles_half;

	if (!radar_is_valid(cub))
		return ;
	player_map_x = (int)(cub->player->pos_x);
	player_map_y = (int)(cub->player->pos_y);
	tiles_half = RADAR_RADIUS / RADAR_SCALE;
	start_x = player_map_x - tiles_half;
	start_y = player_map_y - tiles_half;
	draw_radar_background(cub);
	draw_radar_tiles(cub, start_x, start_y);
	draw_radar_crosshair(cub);
	draw_radar_rings(cub);
	draw_radar_enemies(cub);
	draw_radar_player(cub);
	draw_radar_border(cub);
}
