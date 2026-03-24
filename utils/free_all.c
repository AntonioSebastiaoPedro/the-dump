/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:30:22 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 15:38:11 by paulcard         ###   ########.fr       */
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

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free(game->no);
	free(game->so);
	free(game->we);
	free(game->ea);
	if (game->map)
		free_map(game->map, game->map_height);
}
