/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:22 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/26 12:18:15 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "../includes/cub.h"

void    free_map(char **map, int height)
{
    int i;

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

 void   free_split(char **arr)
{
    int i;
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

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->config)
	{
		free(cub->config->no);
		free(cub->config->so);
		free(cub->config->we);
		free(cub->config->ea);
		free(cub->config);
	}
	if (cub->map)
	{
		if (cub->map->grid)
			free_map(cub->map->grid, cub->map->height);
		free(cub->map);
	}
	if (cub->player)
		free(cub->player);
	if (cub->textures)
		free(cub->textures);
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
	free(cub);
}
