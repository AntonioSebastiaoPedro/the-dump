/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:24:14 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/17 15:24:15 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= cub->mlx->width || y < 0 || y >= cub->mlx->height)
		return ;
	dst = cub->mlx->addr + (y * cub->mlx->line_len + x * (cub->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
