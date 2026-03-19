/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 14:04:30 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 14:04:30 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int	parse_map(char **lines, int map_start, t_game *game)
{
    int     i;
    int     height;
    bool    ln_empty_found;
    char    **map;

    if (!lines || map_start < 0)
        return (ft_putendl_fd("Mapa invalido", 2), 0);
    i = map_start;
    ln_empty_found = false;
    while (lines[i])
    {
        if (is_empty_line(lines[i]))
            ln_empty_found = true;
        else if (ln_empty_found)
            return (ft_putendl_fd("Erro: linha vazia dentro do mapa", 2), 0);
        else if (!is_valid_line_map(lines[i]))
            return (ft_putendl_fd("Erro: caracteres inválidos no mapa", 2), 0);
        i++;
    }
    height = i - map_start;
    if (height == 0)
        return (ft_putendl_fd("Mapa Ausente", 2), 0);
    while (lines[i])
    {
        if (!is_empty_line(lines[i]))
            return (ft_putendl_fd("Erro: mapa deve ser último elemento", 2), 0);
        i++;
    }
    map = copy_map(lines, map_start, height);
    map = normalize_map(map, height);

    if (validate_map(map, height) == 0)
    {
        //free_map(map);
    }
    game->map = map;
    game->map_height = height;
    game->map_width = ft_strlen(map[0]);
    return (1);
}