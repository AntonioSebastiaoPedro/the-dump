/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 18:07:53 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 18:07:53 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int check_inside(char **map)
{
    int i;
    int j;

    i = 1;
    while (map[i + 1])
    {
        j = 1;
        while (map[i][j + 1])
        {
            if (map[i][j] == '0' || is_player(map[i][j]))
            {
                if (map[i - 1][j] == SPACE || map[i + 1][j] == SPACE ||
                    map[i][j - 1] == SPACE || map[i][j + 1] == SPACE)
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}