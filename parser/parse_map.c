/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:30 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 18:46:43 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int	parse_map(char **lines, int map_start, t_game *game)
{
    int     i;
    int     height;
    char    **map;

    if (!lines || map_start < 0)
        return (ft_putendl_fd("Mapa invalido", 2), 0);
    i = map_start;
    height = 0;
    while (lines[i])
    {
        if (is_empty_line(lines[i]))
            break ;
        if (!is_valid_line_map(lines[i]))
            return (ft_putendl_fd("Erro: caracteres inválidos no mapa", 2), 0);
        height++;
        i++;
    }
    if (height == 0)
        return (ft_putendl_fd("Mapa Ausente", 2), 0);
    while (lines[i])
    {
        if (!is_empty_line(lines[i]))
            return (ft_putendl_fd("Erro: mapa deve ser último elemento", 2), 0);
        i++;
    }
    map = copy_map(lines, map_start, height);
    if (!map)
        return (ft_putendl_fd("Erro: falha ao copiar mapa", 2), 0);
    map = normalize_map(map, height);
    if (!map)
        return (ft_putendl_fd("Erro: falha ao normalizar mapa", 2), 0);
    print_map(map);
    game->map_height = height;
    game->map_width = ft_strlen(map[0]);
    if (validate_map(map, height, game) == 0)
        return (free_map(map, height), 0);
    game->map = map;
    return (1);
}
