/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 12:36:46 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 12:36:46 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

t_line_type	get_line_type(const char *line)
{
	if (!line || !line[0])
		return (EMPTY);
	while (*line == SPACE || *line == TAB)
		line++;
	if (*line == '\0' || *line == NEWLINE)
		return (EMPTY);
	if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
	{
		if (line[2] == SPACE || line[2] == TAB || line[2] == NEWLINE)
			return (TEXTURE);
		return (INVALID);
	}
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (line[1] == SPACE || line[1] == NEWLINE || line[1] == TAB)
			return (COLOR);
		return (INVALID);
	}
	if (line[0] == '0' || line[0] == '1' || line[0] == SPACE
		|| line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
		return (MAP);
	return (INVALID);
}
