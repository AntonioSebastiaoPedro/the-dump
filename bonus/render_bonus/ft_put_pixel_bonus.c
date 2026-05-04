/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:42:35 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 23:06:40 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	ft_put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*new_addr;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	new_addr = cub->mlx->addr + (y * cub->mlx->line_len)
		+ (x * (cub->mlx->bpp / 8));
	*(unsigned int *)new_addr = color;
}
