/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_about_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:55:50 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 19:07:08 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	put_line(t_draw *d, char *text)
{
	int	x;

	x = (WIDTH - (ft_strlen(text) * 10)) / 2;
	mlx_string_put(d->cub->mlx->mlx, d->cub->mlx->win, x, *(d->y),
		d->color, text);
	*(d->y) += 20;
}

void	about_write(t_cub *cub)
{
	int		y;
	t_draw	d;

	ft_memset(&d, 0, sizeof(d));
	y = 400;
	d.cub = cub;
	d.margin = 100;
	d.y = &y;
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
	d.color = GREEN;
	(put_line(&d, PP), put_line(&d, PP1));
	y += 30;
	d.color = WHITE;
	put_line(&d, DESC_TITLE);
	d.color = WHITE;
	(put_line(&d, DESC1), put_line(&d, DESC2));
	y += 30;
	put_line(&d, CONCEPT_TITLE);
	(put_line(&d, CONCEPT1), put_line(&d, CONCEPT2));
	(put_line(&d, CONCEPT3), put_line(&d, CONCEPT4), put_line(&d, CONCEPT5));
	y += 30;
	mlx_string_put(cub->mlx->mlx, cub->mlx->win,
		(WIDTH - (ft_strlen(EXIT_MSG) * 10)) / 2, y,
		0xAAAAAA, EXIT_MSG);
}

void	render_about(t_cub *cub)
{
	draw_cover(cub);
	about_write(cub);
}
