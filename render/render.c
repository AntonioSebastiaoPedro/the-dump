/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/14 00:53:17 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	ft_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*new_addr;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	new_addr = cub->mlx->addr + (y * cub->mlx->line_len)
		+ (x * (cub->mlx->bpp / 8));
	*(unsigned int *)new_addr = color;
}

void	draw_vertical_line(t_cub *cub, int col, int line_height, int color)
{
	int	y;
	int	start_y;

	start_y = (HEIGHT - line_height) / 2;
	y = start_y;

	while (y < start_y + line_height)
	{
		ft_put_pixel(cub, col, y, color);
		y++;
	}
}

void	render(t_cub *cub)
{
	unsigned int	*pos;
	int				i;

	i = 0;
	pos = (unsigned int *)cub->mlx->addr;
	while (i < WIDTH * HEIGHT)
		*(pos + i++) = BLACK;

	// Desenhar algumas colunas de teste
	draw_vertical_line(cub, 800, 500, RED);
	draw_vertical_line(cub, 1250, 320, YELLOW);

	ft_put_pixel(cub, WIDTH / 2, HEIGHT / 2, RED);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
