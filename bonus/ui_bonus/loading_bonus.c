/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:27:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/29 14:39:29 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	init_loading(t_loading *loading, void *mlx)
{
	(void)mlx;
	loading->progress = 0;
	loading->max_progress = 100;
	loading->frame_count = 0;
	loading->logo = NULL;
	loading->background = NULL;
}

void	update_loading(t_loading *loading)
{
	if (loading->progress < loading->max_progress)
	{
		loading->frame_count++;
		if (loading->frame_count >= 8)
		{
			loading->progress += 1;
			loading->frame_count = 0;
		}
	}
}

int	is_loading_complete(t_loading *loading)
{
	return (loading->progress >= loading->max_progress);
}

void	draw_rectangle(t_cub *cub, t_ldg_render *ldg, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < ldg->h)
	{
		j = 0;
		while (j < ldg->w)
		{
			ft_put_pixel(cub, ldg->x + j, ldg->y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_texture_img(t_cub *cub, t_texture *tex)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*pixel;

	if (!tex->img)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = tex->addr + (y * tex->line_len
					+ x * (tex->bpp / 8));
			color = *(unsigned int *)pixel;
			ft_put_pixel(cub, x, y, color);
			x++;
		}
		y++;
	}
}
