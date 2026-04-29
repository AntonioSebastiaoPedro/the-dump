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

#include "../includes_bonus/cub_bonus.h"

int	flood_fill(char **map, t_fdfil pos, int height, int width)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= height || pos.x >= width)
		return (0);
	if (map[pos.y][pos.x] == SPACE)
		return (0);
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'F')
		return (1);
	map[pos.y][pos.x] = 'F';
	if (!flood_fill(map, (t_fdfil){pos.x + 1, pos.y}, height, width))
		return (0);
	if (!flood_fill(map, (t_fdfil){pos.x - 1, pos.y}, height, width))
		return (0);
	if (!flood_fill(map, (t_fdfil){pos.x, pos.y + 1}, height, width))
		return (0);
	if (!flood_fill(map, (t_fdfil){pos.x, pos.y - 1}, height, width))
		return (0);
	return (1);
}
