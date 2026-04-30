/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:22 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/30 19:42:40 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	free_config(cub);
	if (cub->map)
	{
		if (cub->map->grid)
			free_map(cub->map->grid, cub->map->height);
		free(cub->map);
	}
	if (cub->door)
		free(cub->door);
	if (cub->player)
		free(cub->player);
	if (cub->textures)
	{
		free_textures(cub);
		free(cub->textures);
	}
	free_mlx(cub);
	free(cub);
}
