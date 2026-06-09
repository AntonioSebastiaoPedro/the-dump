#include "../includes_bonus/cub_bonus.h"

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (free(mlx), NULL);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), free(mlx->mlx), free(mlx), NULL);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		return (free(mlx->mlx), free(mlx), NULL);
	}
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bpp,
			&mlx->line_len,
			&mlx->endian);
	return (mlx);
}