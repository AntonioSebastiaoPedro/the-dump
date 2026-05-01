/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:50:00 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 19:36:08 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	free_weapon_textures(t_cub *cub)
{
	int		state;
	int		frame;
	void	*ptr;

	state = 0;
	while (state < WEAPON_STATES)
	{
		frame = 0;
		while (frame < WEAPON_FRAMES)
		{
			ptr = cub->weapon.frames[state][frame].img;
			if (ptr)
				mlx_destroy_image(cub->mlx->mlx, ptr);
			frame++;
		}
		state++;
	}
}

void	free_door_textures(t_cub *cub)
{
	void	*ptr;
	int		frame;

	frame = 0;
	while (frame < DOOR_FRAMES)
	{
		ptr = cub->textures->door[frame].img;
		if (ptr)
			mlx_destroy_image(cub->mlx->mlx, ptr);
		frame++;
	}
}

void	free_textures(t_cub *cub)
{
	if (!cub || !cub->mlx || !cub->mlx->mlx || !cub->textures)
		return ;
	if (cub->textures->no.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->no.img);
	if (cub->textures->so.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->so.img);
	if (cub->textures->we.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->we.img);
	if (cub->textures->ea.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->ea.img);
	if (cub->menu.cover.img)
		mlx_destroy_image(cub->mlx->mlx, cub->menu.cover.img);
	if (cub->menu.about_img.img)
		mlx_destroy_image(cub->mlx->mlx, cub->menu.about_img.img);
	free_weapon_textures(cub);
	free_door_textures(cub);
}
