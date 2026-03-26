/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-25 14:43:03 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-25 14:43:03 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void    init_mlx(t_mlx *mlx)
{
	mlx->width = 1920;
	mlx->height = 1080;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_error("MLX init failed", mlx);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3D");
	if (!mlx->win)
		exit_error("Window creation failed", mlx);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	if (!mlx->img)
		exit_error("Image creation failed", mlx);
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bpp,
			&mlx->line_len,
			&mlx->endian);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			put_pixel(mlx, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

