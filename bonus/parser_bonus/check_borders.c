/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_borders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 18:07:30 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 18:07:30 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

int	check_borders(char **map, int height, int width)
{
	int	value;
	int	i;

	i = 0;
	while (i < width)
	{
		if (map[0][i] != '1' && !ft_isspace(map[0][i]))
			return (0);
		if (map[height - 1][i] != '1' && !ft_isspace(map[height - 1][i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map[i][0] != '1' && !ft_isspace(map[i][0]))
			return (0);
		value = width - 1;
		while (value >= 0 && ft_isspace(map[i][value]))
			value--;
		if (value >= 0 && map[i][value] != '1')
			return (0);
		i++;
	}
	return (1);
}
