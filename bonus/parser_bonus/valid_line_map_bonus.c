/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:38:12 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 23:05:16 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (ft_putendl_fd("Line do Mapa invalido", 2), 0);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_line_map(char *line)
{
	int	i;

	if (!line)
		return (ft_putendl_fd("Line do Mapa invalido", 2), 0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEWD\t \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}
