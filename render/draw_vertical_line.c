/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:16:31 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/19 02:29:53 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		ft_put_pixel(cub, col, y, 0x87CEEB);
		y++;
	}
	while (y <= ray->draw_end)
	{
		if (ray->side == 1)
			ft_put_pixel(cub, col, y, 0xAAAAAA);
		else
			ft_put_pixel(cub, col, y, 0xFFFFFF);
		y++;
	}
	while (y < HEIGHT)
	{
		ft_put_pixel(cub, col, y, 0x444444);
		y++;
	}
}
