#include "../includes/thedump.h"

void	about_write(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}

void	render_about(t_cub *cub)
{
	draw_texture_img(cub, &cub->menu.about_img);
	about_write(cub);
}