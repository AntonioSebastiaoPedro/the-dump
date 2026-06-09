#include "../includes_bonus/cub_bonus.h"

void	draw_char_pixel(t_cub *cub, int x, int y, int character, int color)
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

void	draw_string_graphics(t_cub *cub, int x, int y, char *str, int color)
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