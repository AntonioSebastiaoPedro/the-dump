/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 12:28:44 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 10:58:52 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

static int	handle_line(char *line, t_cub *cub, int *map_start, int i)
{
	t_line_type	type;

	type = get_line_type(line);
	if (type == TEXTURE)
	{
		if (parse_texture(line, cub) == 0)
			return (0);
	}
	else if (type == COLOR)
	{
		if (parse_color(line, cub) == 0)
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
		ft_putendl_fd("Error\nMapa invalido", 2);
		return (0);
	}
	return (1);
}

static int	is_config_complete(t_cub *cub)
{
	if (!cub->config->no || !cub->config->so || !cub->config->we
		|| !cub->config->ea || cub->config->floor_color == -1
		|| cub->config->ceiling_color == -1)
	{
		ft_putendl_fd("Error\nConfiguracao incompleta", 2);
		return (0);
	}
	return (1);
}

static int	process_config(char **lines, t_cub *cub, int *map_start)
{
	int	i;
	int	res;

	i = 0;
	while (lines[i] != NULL)
	{
		res = handle_line(lines[i], cub, map_start, i);
		if (res == 0)
			return (0);
		if (res == 2)
			break ;
		i++;
	}
	if (*map_start == -1)
	{
		ft_putendl_fd("Error\nFicheiro Nao encontrado no mapa", 2);
		return (0);
	}
	if (!is_config_complete(cub))
		return (0);
	return (1);
}

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = ft_calloc(1, sizeof(t_map));
	cub->config = ft_calloc(1, sizeof(t_config));
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	if (!cub->map || !cub->config || !cub->player || !cub->textures)
		return (free_cub(cub), NULL);
	cub->config->floor_color = -1;
	cub->config->ceiling_color = -1;
	cub->menu.cover.img = NULL;
	return (cub);
}

t_cub	*parse_cub(int ac, char **av)
{
	char	**lines;
	int		map_start;
	t_cub	*cub;

	map_start = -1;
	ft_validate_file(ac, av);
	lines = read_file(av[1]);
	if (!lines)
		return (NULL);
	cub = init_cub();
	if (!cub)
		return (free_split(lines), NULL);
	if (!process_config(lines, cub, &map_start))
	{
		free_split(lines);
		return (free_cub(cub), NULL);
	}
	if (parse_map(lines, map_start, cub) == 0)
	{
		free_split(lines);
		return (free_cub(cub), NULL);
	}
	free_split(lines);
	return (cub);
}
