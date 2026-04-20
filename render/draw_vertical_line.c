/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:16:31 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/21 00:15:37 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_texture	*get_texture(t_ray *ray, t_cub *cub)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (&cub->textures->we);
		else
			return (&cub->textures->ea);
	}
	else
	{
		if (ray->dir_y < 0)
			return (&cub->textures->no);
		else
			return (&cub->textures->so);
	}
	return (NULL);
}

void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int			y;
	int			tex_y;
	int			color;
	t_texture	*tex;

	y = 0;
	tex = get_texture(ray, cub);
	while (y < ray->draw_start)
	{
		ft_put_pixel(cub, col, y, cub->config->ceiling_color);
		y++;
	}
	// WALL (TEXTURE)
	while (y <= ray->draw_end)
	{
		tex_y = (int)ray->texture_pos;
		ray->texture_pos += ray->step_texture;

		/*if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;*/

		color = *(unsigned int *)(tex->addr +
			(tex_y * tex->line_len + ray->texture_column * (tex->bpp / 8)));


		ft_put_pixel(cub, col, y, color);


		y++;
	}
	while (y < HEIGHT)
	{
		ft_put_pixel(cub, col, y, cub->config->floor_color);
		y++;
	}
}
