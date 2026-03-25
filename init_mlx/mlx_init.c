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

void    ft_init_mlx(t_mlx *mlx)
{
	mlx->width = 800;
	mlx->height = 600;

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