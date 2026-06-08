/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/08 09:49:05 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"
#include <X11/Xlib.h>

int	main(int ac, char **av)
{
	t_cub	*cub;

	XInitThreads();

	cub = parse_cub(ac, av);
	if (!cub)
		return (1);
	cub->mlx = init_mlx();
	if (!cub->mlx)
		return (free_cub(cub), 1);
	cub->mouse.center_x = WIDTH / 2;
	cub->mouse.center_y = HEIGHT / 2;
	cub->state = LOADING;
	init_loading(cub, &cub->loading, cub->mlx->mlx);

	// Load and scale UI textures needed for transitions and menu
	if (!load_single_texture(cub, &cub->menu.cover, COVER))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.cover, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.menu_img, MENU_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.menu_img, WIDTH, HEIGHT);
	if (!load_single_texture(cub, &cub->menu.about_img, ABOUT_IMG))
		return (free_cub(cub), 1);
	scale_texture(cub, &cub->menu.about_img, WIDTH, HEIGHT);
	start_loader_thread(cub);
	cub->player_hp = PLAYER_MAX_HP;
	cub->show_mira = true;
	cub->crosshair.scale = 1.0f;
	cub->crosshair.color = GREEN;
	cub->crosshair.enabled = true;
	hook_close(cub);
	mlx_hook(cub->mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx->win, 3, 1L << 1, key_release, cub);
	mlx_mouse_hook(cub->mlx->win, mouse_hook, cub);
	mlx_loop_hook(cub->mlx->mlx, loop_hook, cub);
	(mlx_loop(cub->mlx->mlx), free_cub(cub));
	return (0);
}
