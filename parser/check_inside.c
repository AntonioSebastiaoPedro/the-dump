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

int find_player(char **map, int *x, int *y)
{
    int i = 0;
    int j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
            {
                *x = j;
                *y = i;
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int check_inside(char **map, int height)
{
    char **copy;
    int x;
    int y;

    copy = copy_map(map, 0, height);
    if (!copy)
        return (0);
    if (!find_player(copy, &x, &y))
        return (0);
    if (!flood_fill(copy, x, y))
    {
        free_map(copy, height);
        return (0);
    }
    free_map(copy, height);
    return (1);
}
