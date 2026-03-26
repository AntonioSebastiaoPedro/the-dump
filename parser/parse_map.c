/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:30 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/25 18:55:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	get_map_height(char **lines, int map_start)
{
	int	i;
	int	height;

	i = map_start;
	height = 0;
	while (lines[i])
	{
		if (is_empty_line(lines[i]))
			break ;
		if (!is_valid_line_map(lines[i]))
		{
			ft_putendl_fd("Erro: caracteres inválidos no mapa", 2);
			return (-1);
		}
		height++;
		i++;
	}
	if (height == 0)
		ft_putendl_fd("Mapa Ausente no ficheiro", 2);
	return (height);
}

static int	has_trailing_elements(char **lines, int i)
{
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			ft_putendl_fd("Erro: mapa deve ser último elemento", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static char	**process_map_layout(char **lines, int start, int height)
{
	char	**map;

	map = copy_map(lines, start, height);
	if (!map)
	{
		ft_putendl_fd("Erro: falha ao copiar mapa", 2);
		return (NULL);
	}
	map = normalize_map(map, height);
	if (!map)
	{
		ft_putendl_fd("Erro: falha ao normalizar mapa", 2);
		return (NULL);
	}
	return (map);
}

int	parse_map(char **lines, int map_start, t_game *game)
{
	int		height;
	char	**map;

	if (!lines || map_start < 0)
		return (ft_putendl_fd("Mapa invalido", 2), 0);
	height = get_map_height(lines, map_start);
	if (height <= 0)
		return (0);
	if (has_trailing_elements(lines, map_start + height))
		return (0);
	map = process_map_layout(lines, map_start, height);
	if (!map)
		return (0);
	//print_map(map);
	game->map_height = height;
	game->map_width = ft_strlen(map[0]);
	if (validate_map(map, height, game) == 0)
	{
		free_map(map, height);
		return (0);
	}
	game->map = map;
	return (1);
}
