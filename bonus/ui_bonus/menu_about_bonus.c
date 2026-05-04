/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_about_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:55:50 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 10:01:28 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	about_write(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}

void	render_about(t_cub *cub)
{
	draw_texture_img(cub, &cub->menu.about_img);
	about_write(cub);
}
