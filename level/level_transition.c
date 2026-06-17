#include "../includes/thedump.h"

static void	draw_text_centered(t_cub *cub, char *str, int color, int y_offset)
{
	int	x;
	int	y;

	x = WIDTH / 2 - (ft_strlen(str) * 3); // rough approximation
	y = HEIGHT / 2 + y_offset;
	mlx_string_put(cub->mlx->mlx, cub->mlx->win, x, y, color, str);
}

void	render_transition_screen(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		((unsigned int *)cub->mlx->addr)[i++] = BLACK;
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	draw_text_centered(cub, "LEVEL COMPLETED", GREEN, -20);
	draw_text_centered(cub, "Press ENTER to continue", WHITE, 20);
}

void	render_game_over(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		((unsigned int *)cub->mlx->addr)[i++] = DARK_RED;
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	draw_text_centered(cub, "GAME OVER", WHITE, -20);
	draw_text_centered(cub, "Press ESC to Quit", WHITE, 20);
}

void	render_victory_screen(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		((unsigned int *)cub->mlx->addr)[i++] = LIGHT_GRAY;
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	draw_text_centered(cub, "YOU ESCAPED!", GREEN, -20);
	draw_text_centered(cub, "Congratulations!", WHITE, 20);
	draw_text_centered(cub, "Press ESC to Quit", WHITE, 60);
}
