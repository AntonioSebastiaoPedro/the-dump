#include "../includes/thedump.h"

static void	draw_line(t_cub *cub, int x0, int y0, int x1, int y1, int color)
{
	int	dx = abs(x1 - x0);
	int	dy = -abs(y1 - y0);
	int	sx = x0 < x1 ? 1 : -1;
	int	sy = y0 < y1 ? 1 : -1;
	int	err = dx + dy;
	int	e2;

	while (1)
	{
		ft_put_pixel(cub, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	draw_circle(t_cub *cub, int xm, int ym, int r, int color)
{
	int	x = -r;
	int	y = 0;
	int	err = 2 - 2 * r;

	do {
		ft_put_pixel(cub, xm - x, ym + y, color);
		ft_put_pixel(cub, xm - y, ym - x, color);
		ft_put_pixel(cub, xm + x, ym - y, color);
		ft_put_pixel(cub, xm + y, ym + x, color);
		r = err;
		if (r <= y)
			err += ++y * 2 + 1;
		if (r > x || err > y)
			err += ++x * 2 + 1;
	} while (x < 0);
}

static void	draw_center_dot(t_cub *cub, int cx, int cy, float scale)
{
	draw_circle(cub, cx, cy, (int)(3 * scale), cub->crosshair.color);
}

static void	draw_open_square(t_cub *cub, int cx, int cy, float scale)
{
	int	size = (int)(15 * scale);
	int	corner = (int)(5 * scale);
	int	color = cub->crosshair.color;

	// Top-left
	draw_line(cub, cx - size, cy - size, cx - size + corner, cy - size, color);
	draw_line(cub, cx - size, cy - size, cx - size, cy - size + corner, color);
	// Top-right
	draw_line(cub, cx + size, cy - size, cx + size - corner, cy - size, color);
	draw_line(cub, cx + size, cy - size, cx + size, cy - size + corner, color);
	// Bottom-left
	draw_line(cub, cx - size, cy + size, cx - size + corner, cy + size, color);
	draw_line(cub, cx - size, cy + size, cx - size, cy + size - corner, color);
	// Bottom-right
	draw_line(cub, cx + size, cy + size, cx + size - corner, cy + size, color);
	draw_line(cub, cx + size, cy + size, cx + size, cy + size - corner, color);
}

static void	draw_main_lines(t_cub *cub, int cx, int cy, float scale)
{
	int	gap = (int)(25 * scale);
	int	len = (int)(40 * scale);
	int	color = cub->crosshair.color;

	draw_line(cub, cx - gap, cy, cx - gap - len, cy, color); // Left
	draw_line(cub, cx + gap, cy, cx + gap + len, cy, color); // Right
	draw_line(cub, cx, cy - gap, cx, cy - gap - len, color); // Top
	draw_line(cub, cx, cy + gap, cx, cy + gap + len, color); // Bottom
}

static void	draw_ticks(t_cub *cub, int cx, int cy, float scale)
{
	int	spacing = (int)(8 * scale);
	int	size = (int)(4 * scale);
	int	color = cub->crosshair.color;
	int	i;

	i = 1;
	while (i <= 4)
	{
		int offset = (int)(25 * scale) + i * spacing;
		draw_line(cub, cx - offset, cy - size, cx - offset, cy + size, color);
		draw_line(cub, cx + offset, cy - size, cx + offset, cy + size, color);
		draw_line(cub, cx - size, cy - offset, cx + size, cy - offset, color);
		draw_line(cub, cx - size, cy + offset, cx + size, cy + offset, color);
		i++;
	}
}

void	draw_mira(t_cub *cub)
{
	int		cx;
	int		cy;
	float	scale;

	if (!cub->show_mira || !cub->crosshair.enabled)
		return ;
	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	scale = cub->crosshair.scale;
	draw_center_dot(cub, cx, cy, scale);
	draw_open_square(cub, cx, cy, scale);
	draw_main_lines(cub, cx, cy, scale);
	draw_ticks(cub, cx, cy, scale);
}
