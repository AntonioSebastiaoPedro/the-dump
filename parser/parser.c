/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:28:44 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/25 18:47:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static int	handle_line(char *line, t_game *game, int *map_start, int i)
{
	t_line_type	type;

	type = get_line_type(line);
	if (type == TEXTURE)
	{
		if (parse_texture(line, game) == 0)
			return (0);
	}
	else if (type == COLOR)
	{
		if (parse_color(line, game) == 0)
			return (0);
	}
	else if (type == MAP)
	{
		if (*map_start == -1)
			*map_start = i;
		return (2);
	}
	else if (type == INVALID && line[0] != '\0')
	{
		ft_putendl_fd("Mapa invalido", 2);
		return (0);
	}
	return (1);
}

static int	process_config(char **lines, t_game *game, int *map_start)
{
	int	i;
	int	res;

	i = 0;
	while (lines[i] != NULL)
	{
		res = handle_line(lines[i], game, map_start, i);
		if (res == 0)
			return (0);
		if (res == 2)
			break ;
		i++;
	}
	if (*map_start == -1)
	{
		ft_putendl_fd("Ficheiro Nao encontrado no mapa", 2);
		return (0);
	}
	return (1);
}

int	parser(int ac, char **av, t_game *game)
{
	char	**lines;
	int		map_start;

	map_start = -1;
	ft_validate_file(ac, av);
	lines = read_file(av[1]);
	if (!lines)
		return (0);
	if (!process_config(lines, game, &map_start))
	{
		free_split(lines);
		return (0);
	}
	if (parse_map(lines, map_start, game) == 0)
	{
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}
