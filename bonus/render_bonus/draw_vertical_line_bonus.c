/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 02:16:31 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 19:45:05 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

unsigned int	get_texture_color(t_texture *texture, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(texture->addr + (y * texture->line_len)
			+ (x * (texture->bpp / 8)));
	return (color);
}

static void	put_fc_color(t_cub *cub, int col, int y, int is_floor)
{
	if (is_floor)
		ft_put_pixel(cub, col, y, cub->config->floor_color);
	else
		ft_put_pixel(cub, col, y, cub->config->ceiling_color);
}

static void	draw_floor_ceiling_pixel(t_cub *cub, int col, int y,
	int is_floor, t_ray *ray)
{
	double	cur_dist;
	double	floor_x;
	double	floor_y;
	int		tx;
	int		ty;

	if (is_floor && !cub->config->f_tex)
		return (put_fc_color(cub, col, y, is_floor));
	if (!is_floor && !cub->config->c_tex)
		return (put_fc_color(cub, col, y, is_floor));
	if (is_floor)
		cur_dist = (double)HEIGHT / (2.0 * y - HEIGHT);
	else
		cur_dist = (double)HEIGHT / (HEIGHT - 2.0 * y);
	floor_x = cub->player->pos_x + cur_dist * ray->dir_x;
	floor_y = cub->player->pos_y + cur_dist * ray->dir_y;
	tx = (int)(floor_x * (is_floor ? cub->textures->floor.width
				: cub->textures->ceiling.width)) % (is_floor ? cub->textures->floor.width
			: cub->textures->ceiling.width);
	ty = (int)(floor_y * (is_floor ? cub->textures->floor.height
				: cub->textures->ceiling.height)) % (is_floor ? cub->textures->floor.height
			: cub->textures->ceiling.height);
	if (tx < 0)
		tx += (is_floor ? cub->textures->floor.width : cub->textures->ceiling.width);
	if (ty < 0)
		ty += (is_floor ? cub->textures->floor.height : cub->textures->ceiling.height);
	ft_put_pixel(cub, col, y, get_texture_color(is_floor ? &cub->textures->floor
			: &cub->textures->ceiling, tx, ty));
}

void	draw_vertical_line(int col, t_ray *ray, t_cub *cub)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	t_texture		*texture;

	y = 0;
	texture = get_texture(ray, cub);
	while (y < ray->draw_start)
	{
		draw_floor_ceiling_pixel(cub, col, y, 0, ray);
		y++;
	}
	while (y <= ray->draw_end)
	{
		tex_y = (int)ray->texture_pos;
		ray->texture_pos += ray->step_texture;
		color = get_texture_color(texture, ray->texture_column, tex_y);
		ft_put_pixel(cub, col, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		draw_floor_ceiling_pixel(cub, col, y, 1, ray);
		y++;
	}
}
