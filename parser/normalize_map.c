/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 11:38:10 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 11:38:10 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"


static int find_max_len(char **map, int height)
{
    int max_len = 0;
    int len;
    int i = 0;

    while (i < height)
    {
        len = ft_strlen(map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    return (max_len);
}

static char *pad_line(char *line, int max_len)
{
    char    *new_line;
    int     i = 0;
    int     len;

    if (!line)
        return (NULL);

    len = ft_strlen(line);
    new_line = malloc(max_len + 1);
    if (!new_line)
        return (NULL);

    while (i < len)
    {
        new_line[i] = line[i];
        i++;
    }
    while (i < max_len)
    {
        new_line[i] = SPACE;
        i++;
    }
    new_line[i] = '\0';
    return (new_line);
}

char    **normalize_map(char **map, int height)
{
    char    *tmp;
    int     i;
    int     max_len;

    if (!map)
        return (NULL);

    max_len = find_max_len(map, height);
    i = 0;
    while (i < height)
    {
        tmp = map[i];
        map[i] = pad_line(map[i], max_len);
        free(tmp);
        i++;
    }
    return (map);
}