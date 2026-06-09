#include "../includes_bonus/cub_bonus.h"

static void	draw_button(t_cub *cub, int y, int index, char *label)
{
	int	color;

	if (cub->menu.selected == index)
	{
		color = GREEN;
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			WIDTH / 2 - 130, y, color, label);
	}
	else
	{
		color = WHITE;
		mlx_string_put(cub->mlx->mlx, cub->mlx->win,
			WIDTH / 2 - 100, y, color, label + 2);
	}
}

void	switch_button(t_cub *cub)
{
	int	y;

	y = HEIGHT / 2 + 75;
	draw_button(cub, y, 0, ">");
	y += 90;
	draw_button(cub, y, 1, ">");
	y += 90;
	draw_button(cub, y, 2, ">");
}

void	render_menu(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ft_put_pixel(cub, i, j, BG_COLOR);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	if (cub->menu.menu_img.img)
		mlx_put_image_to_window(cub->mlx->mlx,
			cub->mlx->win, cub->menu.menu_img.img, 0, 0);
	switch_button(cub);
}
