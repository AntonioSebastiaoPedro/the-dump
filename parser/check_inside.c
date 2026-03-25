/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:07:53 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 18:47:50 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int check_inside(char **map, int height, t_game *game)
{
    char **copy;

    copy = copy_map(map, 0, height);
    if (!copy)
        return (0);
    if (!flood_fill(copy, game->player_x, game->player_y))
    {
        free_map(copy, height);
        return (0);
    }
    free_map(copy, height);
    return (1);
}
