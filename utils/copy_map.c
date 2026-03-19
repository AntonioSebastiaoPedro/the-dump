/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 11:23:19 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 11:23:19 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

char    **copy_map(char **lines, int map_start, int height)
{
    char    **map;
    int     i;

    if (!lines)
        return (NULL);
    map = (char **)malloc((height + 1) * sizeof(char *));
    if (!map)
        return (NULL);
    i = 0;
    while (i < height)
    {
        map[i] = ft_strdup(lines[map_start + i]);
        i++;
    }
    map[i] = NULL;
    return (map);
}