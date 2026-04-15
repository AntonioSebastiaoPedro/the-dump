/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:30 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 10:57:54 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

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
			ft_putendl_fd("Error\ncaracteres inválidos no mapa", 2);
			return (-1);
		}
		height++;
		i++;
	}
	if (height == 0)
		ft_putendl_fd("Error\nMapa Ausente no ficheiro", 2);
	return (height);
}

static int	has_trailing_elements(char **lines, int i)
{
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			ft_putendl_fd("Error\nMapa deve ser último elemento", 2);
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
		ft_putendl_fd("Error\nfalha ao copiar mapa", 2);
		return (NULL);
	}
	map = normalize_map(map, height);
	if (!map)
	{
		ft_putendl_fd("Error\nfalha ao normalizar mapa", 2);
		return (NULL);
	}
	return (map);
}

int	parse_map(char **lines, int map_start, t_cub *cub)
{
	int		height;
	char	**grid;

	if (!lines || map_start < 0)
		return (ft_putendl_fd("Error\nMapa invalido", 2), 0);
	height = get_map_height(lines, map_start);
	if (height <= 0)
		return (0);
	if (has_trailing_elements(lines, map_start + height))
		return (0);
	grid = process_map_layout(lines, map_start, height);
	if (!grid)
		return (0);
	cub->map->height = height;
	cub->map->width = ft_strlen(grid[0]);
	cub->map->grid = grid;
	if (validate_map(grid, height, cub) == 0)
	{
		free_map(grid, height);
		cub->map->grid = NULL;
		return (0);
	}
	return (1);
}
