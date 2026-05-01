/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:50:00 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/01 19:46:58 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	free_weapon_textures(t_cub *cub)
{
	int		state;
	int		frame;
	void	*img_ptr;

	state = 0;
	while (state < WEAPON_STATES)
	{
		frame = 0;
		while (frame < WEAPON_FRAMES)
		{
			img_ptr = cub->weapon.frames[state][frame].img;
			if (img_ptr)
				mlx_destroy_image(cub->mlx->mlx, img_ptr);
			frame++;
		}
		state++;
	}
}

void	free_door_textures(t_cub *cub)
{
	int		i;
	void	*img_ptr;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		img_ptr = cub->door_frames[i].img;
		if (img_ptr)
			mlx_destroy_image(cub->mlx->mlx, img_ptr);
		i++;
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
	if (cub->textures->floor.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->floor.img);
	if (cub->textures->ceiling.img)
		mlx_destroy_image(cub->mlx->mlx, cub->textures->ceiling.img);
	free_weapon_textures(cub);
	free_door_textures(cub);
}
