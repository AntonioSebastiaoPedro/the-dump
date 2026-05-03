/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:04:43 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 00:52:58 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	load_single_texture(t_cub *cub, t_texture *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		ft_putendl_fd("Error\nNão foi possível carregar alguma textura", 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	load_weapon(t_cub *cub, const char *paths[WEAPON_STATES][WEAPON_FRAMES])
{
	int			state;
	int			frame;

	state = 0;
	while (state < WEAPON_STATES)
	{
		frame = 0;
		while (frame < WEAPON_FRAMES)
		{
			if (paths[state][frame] == NULL)
			{
				frame++;
				continue ;
			}
			if (!load_single_texture(cub
					, &cub->weapon.frames[state][frame], paths[state][frame]))
				return (0);
			frame++;
		}
		state++;
	}
	cub->weapon.state = WEAPON_IDLE;
	cub->weapon.current_frame = 0;
	cub->weapon.frame_timer = 0;
	return (set_weapon_state(&cub->weapon, WEAPON_IDLE), 1);
}

int	load_weapon_textures(t_cub *cub)
{
	const char	*paths[WEAPON_STATES][WEAPON_FRAMES] = {
	{
		"assets/weapon/idle/idle1.xpm",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	},
	{
		"assets/weapon/move/move1.xpm", "assets/weapon/move/move2.xpm",
		"assets/weapon/move/move3.xpm", "assets/weapon/move/move4.xpm",
		"assets/weapon/move/move5.xpm", "assets/weapon/move/move6.xpm",
		"assets/weapon/move/move7.xpm",
		NULL, NULL
	},
	{
		"assets/weapon/shot/frame1.xpm", "assets/weapon/shot/frame2.xpm",
		"assets/weapon/shot/frame3.xpm", "assets/weapon/shot/frame4.xpm",
		"assets/weapon/shot/frame5.xpm", "assets/weapon/shot/frame6.xpm",
		"assets/weapon/shot/frame7.xpm", "assets/weapon/shot/frame8.xpm",
		"assets/weapon/shot/frame9.xpm",
	},
	};

	if (!load_weapon(cub, paths))
		return (0);
	return (1);
}

int	load_door(t_cub *cub, const char *paths[DOOR_FRAMES])
{
	int	frame;

	frame = 0;
	while (frame < DOOR_FRAMES)
	{
		if (!load_single_texture(cub,
				&cub->textures->door[frame], paths[frame]))
			return (0);
		frame++;
	}
	return (1);
}

int	load_door_textures(t_cub *cub)
{
	const char *paths[DOOR_FRAMES] = {
		"assets/door/door0.xpm",
		"assets/door/door1.xpm",
		"assets/door/door2.xpm",
		"assets/door/door3.xpm",
		"assets/door/door4.xpm",
		"assets/door/door5.xpm",
		"assets/door/door6.xpm",
		"assets/door/door7.xpm",
		"assets/door/door8.xpm",
	};
	if (!load_door(cub, paths))
		return (0);
	return (1);
}

int	load_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->textures->no, cub->config->no))
		return (0);
	if (!load_single_texture(cub, &cub->textures->so, cub->config->so))
		return (0);
	if (!load_single_texture(cub, &cub->textures->we, cub->config->we))
		return (0);
	if (!load_single_texture(cub, &cub->textures->ea, cub->config->ea))
		return (0);
	if (!load_single_texture(cub, &cub->menu.cover, COVER))
		return (0);
	if (!load_single_texture(cub, &cub->menu.about_img, ABOUT_IMG))
		return (0);
	if (!load_weapon_textures(cub))
		return (0);
	if (!load_door_textures(cub))
		return (0);
	scale_texture(cub, &cub->menu.cover, WIDTH, HEIGHT);
	scale_texture(cub, &cub->menu.about_img, WIDTH, HEIGHT);
	return (1);
}
