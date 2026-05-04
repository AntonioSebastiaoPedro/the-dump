/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:17:56 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 23:06:26 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	update_mouse(t_cub *cub)
{
	int	x;
	int	y;

	if (cub->mouse.show_mouse)
		return ;
	mlx_mouse_get_pos(cub->mlx->mlx, cub->mlx->win, &x, &y);
	cub->mouse.delta_x = x - cub->mouse.center_x;
	if (cub->mouse.delta_x != 0)
	{
		rotate(cub->player, cub->mouse.delta_x * MOUSE_SENSITIVITY);
		mlx_mouse_move(cub->mlx->mlx, cub->mlx->win,
			cub->mouse.center_x, cub->mouse.center_y);
	}
}
