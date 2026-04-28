/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 20:51:34 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/28 15:50:08 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
	map = NULL;
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_config(t_cub *cub)
{
	if (cub->config)
	{
		if (cub->config->no)
			free(cub->config->no);
		if (cub->config->so)
			free(cub->config->so);
		if (cub->config->we)
			free(cub->config->we);
		if (cub->config->ea)
			free(cub->config->ea);
		free(cub->config);
	}
}

void	free_mlx(t_cub *cub)
{
	if (cub->mlx)
	{
		if (cub->mlx->img)
			mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
		if (cub->mlx->win)
			mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
		if (cub->mlx->mlx)
		{
			mlx_destroy_display(cub->mlx->mlx);
			free(cub->mlx->mlx);
		}
		free(cub->mlx);
		cub->mlx = NULL;
	}
}
