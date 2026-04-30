/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/30 16:29:27 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	main(int ac, char **av)
{
	t_cub	*cub;

	cub = parse_cub(ac, av);
	if (!cub)
		return (1);
	cub->mlx = init_mlx();
	if (!cub->mlx)
		return (free_cub(cub), 1);
	cub->mouse.center_x = WIDTH / 2;
	cub->mouse.center_y = HEIGHT / 2;
	cub->state = MENU;
	init_loading(&cub->loading, cub->mlx->mlx);
	if (!init_player(cub))
		return (free_cub(cub), 1);
	if (!load_textures(cub))
		return (free_cub(cub), 1);
	hook_close(cub);
	mlx_hook(cub->mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx->win, 3, 1L << 1, key_release, cub);
	mlx_mouse_hook(cub->mlx->win, mouse_hook, cub);
	mlx_loop_hook(cub->mlx->mlx, loop_hook, cub);
	mlx_loop(cub->mlx->mlx);
	free_cub(cub);
	return (0);
}
