/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 17:29:20 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 10:59:45 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

int	validate_map(char **map, int height, t_cub *cub)
{
	int	width;

	width = ft_strlen(map[0]);
	if (height < 3 || width < 3)
		return (ft_putendl_fd("Error\nmapa muito pequeno", 2), 0);
	if (check_player(map, cub) == 0)
		return (0);
	if (check_borders(map, height, width) == 0)
		return (ft_putendl_fd("Error\nmapa não fechado nas bordas", 2), 0);
	if (check_inside(map, height, cub) == 0)
		return (ft_putendl_fd("Error\nmapa aberto no interior", 2), 0);
	return (1);
}
