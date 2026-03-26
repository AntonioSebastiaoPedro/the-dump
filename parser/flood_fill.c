/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-25 08:06:28 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-25 13:26:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	flood_fill(char **map, int x, int y, int height, int width)
{
	if (x < 0 || y < 0 || y >= height || x >= width)
		return (0);
	if (map[y][x] == SPACE)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return (1);
	map[y][x] = 'F';
	if (!flood_fill(map, x + 1, y, height, width))
		return (0);
	if (!flood_fill(map, x - 1, y, height, width))
		return (0);
	if (!flood_fill(map, x, y + 1, height, width))
		return (0);
	if (!flood_fill(map, x, y - 1, height, width))
		return (0);
	return (1);
}
