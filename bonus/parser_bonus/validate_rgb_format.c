/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 08:26:31 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/21 09:15:44 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static void	skip_spaces(const char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n'
			|| line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

static int	parse_number(const char *line, int *i)
{
	if (!ft_isdigit(line[*i]))
		return (0);
	while (ft_isdigit(line[*i]))
		(*i)++;
	return (1);
}

static int	handle_comma(int *i, int *expecting_number, int *comma)
{
	if (*expecting_number)
		return (0);
	(*comma)++;
	*expecting_number = 1;
	(*i)++;
	return (1);
}

int	validate_rgb_format(const char *line)
{
	int	i;
	int	comma;
	int	expecting_number;

	i = 2;
	comma = 0;
	expecting_number = 1;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (parse_number(line, &i))
			expecting_number = 0;
		else if (line[i] == COMMA)
		{
			if (!handle_comma(&i, &expecting_number, &comma))
				return (0);
		}
		else
			return (0);
	}
	return (!expecting_number && comma == 2);
}
