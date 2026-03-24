/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:23:19 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 18:42:41 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static void remove_newline(char *line)
{
    int i = 0;

    if (!line)
        return;
    while (line[i])
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            return;
        }
        i++;
    }
}

static char *trim_left(char *str)
{
    while (*str == ' ')
        str++;
    return (str);
}

char    **copy_map(char **lines, int map_start, int height)
{
    char    **map;
    char    *clean;
    int     i;

    map = malloc((height + 1) * sizeof(char *));
    if (!map)
        return (NULL);

    i = 0;
    while (i < height)
    {
        remove_newline(lines[map_start + i]);
        clean = trim_left(lines[map_start + i]);
        map[i] = ft_strdup(clean);
        if (!map[i])
            return (NULL);
        i++;
    }
    map[i] = NULL;
    return (map);
}