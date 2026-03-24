/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 18:07:30 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 18:07:30 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int check_borders(char **map, int height, int width)
{
    int value;
    int i;

    i = 0;
    while (i < width)
    {
        if (map[0][i] != '1' && map[0][i] != SPACE)
            return (0);
        if (map[0][height - 1] != '1' && map[0][height - 1] != SPACE)
            return (0);
        i++;
    }
    i = 0;
    while (i < height)
    {
        if (map[i][0] != '1' && map[i][0] != SPACE)
            return (0);
        value = width - 1;
        while (map[i][value] == SPACE)
            value--;
        if (map[i][value] != '1' && map[i][value] != SPACE)
            return (0);
        i++;
    }
    return (1);
}