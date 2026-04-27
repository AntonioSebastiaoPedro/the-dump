/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_about.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:55:50 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 16:13:16 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	put_line(t_draw *d, char *text)
{
	mlx_string_put(d->cub->mlx->mlx, d->cub->mlx->win, d->margin, *(d->y),
		d->color, text);
	*(d->y) += 20;
}

void	about_write(t_cub *cub)
{
	int		y;
	t_draw	d;

	y = 50;
	d.cub = cub;
	d.margin = 50;
	d.y = &y;
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	d.color = GREEN;
	put_line(&d, PP);
	(put_line(&d, PP1), put_line(&d, PP2));
	y += 20;
	d.color = WHITE;
	put_line(&d, DESC_TITLE);
	d.color = LIGHT_GRAY;
	put_line(&d, DESC1);
	(put_line(&d, DESC2), put_line(&d, DESC3));
	(put_line(&d, DESC4), put_line(&d, DESC5));
	y += 20;
	put_line(&d, CONCEPT_TITLE);
	(put_line(&d, CONCEPT1), put_line(&d, CONCEPT2));
	(put_line(&d, CONCEPT3), put_line(&d, CONCEPT4), put_line(&d, CONCEPT5));
	y += 80;
	mlx_string_put(cub->mlx->mlx, cub->mlx->win, 300, y, 0xAAAAAA, EXIT_MSG);
}

void	render_about(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			ft_put_pixel(cub, i, j, BLACK);
			j++;
		}
		i++;
	}
	about_write(cub);
}
