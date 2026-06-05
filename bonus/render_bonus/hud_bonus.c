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

void	draw_texture_hud(t_cub *cub, t_texture *tex, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	if (!tex || !tex->img)
		return ;
	i = 0;
	while (i < tex->height)
	{
		j = 0;
		while (j < tex->width)
		{
			color = *(unsigned int *)(tex->addr + (i * tex->line_len
						+ j * (tex->bpp / 8)));
			// Ignore transparent red (0xFF0000) and standard black/null transparency
			if (color != TRANSPARENT_BACKGROUND && (color & 0x00FFFFFF) != 0)
				pixel_put(cub, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_char_pixel(t_cub *cub, int x, int y, int character, int color)
{
	static const unsigned char font[11][5] = {
		{0x7, 0x5, 0x5, 0x5, 0x7}, // 0
		{0x2, 0x6, 0x2, 0x2, 0x7}, // 1
		{0x7, 0x1, 0x7, 0x4, 0x7}, // 2
		{0x7, 0x1, 0x7, 0x1, 0x7}, // 3
		{0x5, 0x5, 0x7, 0x1, 0x1}, // 4
		{0x7, 0x4, 0x7, 0x1, 0x7}, // 5
		{0x7, 0x4, 0x7, 0x5, 0x7}, // 6
		{0x7, 0x1, 0x1, 0x1, 0x1}, // 7
		{0x7, 0x5, 0x7, 0x5, 0x7}, // 8
		{0x7, 0x5, 0x7, 0x1, 0x1}, // 9
		{0x1, 0x2, 0x4, 0x2, 0x1}  // /
	};
	int i, j;
	int char_idx = (character >= '0' && character <= '9') ? (character - '0') : 10;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 3; j++) {
			if ((font[char_idx][i] >> (2 - j)) & 1) {
				for (int dx = 0; dx < 3; dx++) // Scale 3x
					for (int dy = 0; dy < 3; dy++)
						pixel_put(cub, x + j * 3 + dx, y + i * 3 + dy, color);
			}
		}
	}
}

static void	draw_string_graphics(t_cub *cub, int x, int y, char *str, int color)
{
	while (*str)
	{
		if ((*str >= '0' && *str <= '9') || *str == '/')
		{
			draw_char_pixel(cub, x, y, *str, color);
			x += 15; // 3 blocks * 3 pixels + padding
		}
		else if (*str == ' ')
			x += 10;
		str++;
	}
}

void	draw_ammo_hud(t_cub *cub)
{
	t_vec		start;
	t_vec		size;
	t_weapon	*w;
	char		ammo_str[64];
	int			icon_x;
	int			icon_y;

	w = cub->current_weapon;
	if (!w)
		return ;

	start.x = 20;
	start.y = HEIGHT - 110;
	size.x = 250;
	size.y = 80;

	draw_filled_rect(cub, start, size, BG_COLOR);
	draw_empty_rect(cub, start, size, WHITE);

	if (w->hud_icon.img)
	{
		icon_x = start.x + 8;
		icon_y = start.y + (size.y - w->hud_icon.height) - 13;
		draw_texture_hud(cub, &w->hud_icon, icon_x, icon_y);
	}

	ft_sprintf(ammo_str, "%d / %d", w->current_ammo, w->reserve_ammo);
	draw_string_graphics(cub, start.x + 110, start.y + 35, ammo_str, WHITE);

	if (w->current_ammo == 0 && w->reserve_ammo == 0)
		draw_string_graphics(cub, start.x + 110, start.y + 55, "0 / 0", RED);
}
