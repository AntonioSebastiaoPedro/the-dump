/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 09:38:12 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 11:04:39 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
		return (ft_putendl_fd("Error\nLine do Mapa invalido", 2), 0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW\t \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}
