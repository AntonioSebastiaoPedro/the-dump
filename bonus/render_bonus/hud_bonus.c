#include "../includes_bonus/cub_bonus.h"

void	pixel_put(t_cub *cub, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	ft_put_pixel(cub, x, y, color);
}

void	draw_empty_rect(t_cub *cub, t_vec start, t_vec rect_size, uint32_t color)
{
	t_vec	i;

	i = start;
	while (i.y < rect_size.y + start.y && i.y < HEIGHT)
	{
		if (i.y - start.y == 0 || i.y - start.y >= rect_size.y - 1)
			pixel_put(cub, i.x, i.y, color);
		else if (i.x - start.x == 0 || i.x >= start.x + rect_size.x - 1)
			pixel_put(cub, i.x, i.y, color);
		i.x++;
		if (i.x >= start.x + rect_size.x || i.x >= WIDTH)
		{
			i.x = start.x;
			i.y++;
		}
	}
}

void	draw_filled_rect(t_cub *cub, t_vec start, t_vec size, uint32_t color)
{
	int	x;
	int	y;

	y = (int)start.y;
	while (y < start.y + size.y && y < HEIGHT)
	{
		x = (int)start.x;
		while (x < start.x + size.x && x < WIDTH)
		{
			pixel_put(cub, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_hp_hud(t_cub *cub)
{
	t_vec	start;
	t_vec	size;
	t_vec	hp_size;
	int		hp_width;

	// Background/Border box
	start.x = WIDTH - 220;
	start.y = 20;
	size.x = 200;
	size.y = 40;
	draw_empty_rect(cub, start, size, WHITE);

	// HP Bar
	hp_width = (int)((cub->player_hp / 100.0) * 196);
	if (hp_width < 0) hp_width = 0;
	
	start.x += 2;
	start.y += 2;
	hp_size.x = hp_width;
	hp_size.y = 36;
	
	int color = GREEN;
	if (cub->player_hp < 30)
		color = RED;
	else if (cub->player_hp < 60)
		color = YELLOW;
	
	draw_filled_rect(cub, start, hp_size, color);
}
