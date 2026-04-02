/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:43:03 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/02 12:41:51 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

t_mlx    *init_mlx(void)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (free(mlx), NULL);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width, mlx->height, "Cub3D");
	if (!mlx->win)
		return (mlx_destroy_display(mlx->mlx), free(mlx->mlx), free(mlx), NULL);
	mlx->img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
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

