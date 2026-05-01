/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:30 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/01 16:06:47 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

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

int	count_door(t_cub *cub)
{
	int	n_door;
	int	i;
	int	j;

	n_door = 0;
	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (j < cub->map->width)
		{
			if (cub->map->grid[i][j] == 'D')
				n_door++;
			j++;
		}
		i++;
	}
	return (n_door);
}

void	add_door(t_cub *cub, int x, int y)
{
	cub->door[cub->n_door].x = x;
	cub->door[cub->n_door].y = y;
	cub->door[cub->n_door].state = DOOR_CLOSED;
	cub->door[cub->n_door].frame = 0;
	cub->door[cub->n_door].timer = 0;
	cub->n_door++;
}

int	init_door(t_cub *cub)
{
	int	x;
	int	y;

	cub->n_door = 0;
	cub->door = (t_door *)malloc(count_door(cub) * sizeof(t_door));
	if (!cub->door)
		return (0);
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (cub->map->grid[y][x] == 'D')
				add_door(cub, x, y);
			x++;
		}
		y++;
	}
	return (1);
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
		return (free_map(grid, height), cub->map->grid = NULL,0);
	if (!init_door(cub))
		return (free_map(grid, height), cub->map->grid = NULL,0);
	return (1);
}
