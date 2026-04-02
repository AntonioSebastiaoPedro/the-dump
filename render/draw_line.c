/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:42:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/01 15:42:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void	draw_ver_line(t_cub *cub, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(cub, x, y, cub->ceiling_color);
		y++;
	}
	while (y <= ray->draw_end)
	{
		put_pixel(cub, x, y, ray->color);
		y++;
	}
	while (y < cub->mlx->height)
	{
		put_pixel(cub, x, y, cub->floor_color);
		y++;
	}
}
