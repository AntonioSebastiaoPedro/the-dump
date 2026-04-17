/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:07:53 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/17 10:53:58 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_no_space_adjacent(char **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (is_walkable(map[y][x]))
			{
				if (x == 0 || x == width - 1)
					return (0);
				if (y == 0 || y == height - 1)
					return (0);
				if (ft_isspace(map[y][x + 1]) || ft_isspace(map[y][x - 1]))
					return (0);
				if (ft_isspace(map[y + 1][x]) || ft_isspace(map[y - 1][x]))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_inside(char **map, int height, t_cub *cub)
{
	char	**copy;
	int		width;

	width = ft_strlen(map[0]);
	if (!check_no_space_adjacent(map, height, width))
		return (0);
	copy = copy_map(map, 0, height);
	if (!copy)
		return (0);
	if (!flood_fill(copy, (t_fdfil){(int)cub->player->pos_x,
			(int)cub->player->pos_y}, height, width))
	{
		free_map(copy, height);
		return (0);
	}
	free_map(copy, height);
	return (1);
}
