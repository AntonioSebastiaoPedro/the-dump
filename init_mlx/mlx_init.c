/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:43:03 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 13:35:49 by paulcard         ###   ########.fr       */
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
		free(mlx->mlx);
		return (free(mlx), NULL);
	}
	mlx->addr = mlx_get_data_addr(mlx->img,
			&mlx->bpp,
			&mlx->line_len,
			&mlx->endian);
	return (mlx);
}

void	render(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < cub->mlx->height)
	{
		if (y < cub->mlx->height / 2)
			color = cub->ceiling_color;
		else
			color = cub->floor_color;
		x = 0;
		while (x < cub->mlx->width)
		{
			put_pixel(cub, x, y, color);
			x++;
		}
		y++;
	}
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}

