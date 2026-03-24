/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 15:23:38 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static int	validate_identifier(const char *line, char *id)
{
	if (!line || (line[0] != 'F' && line[0] != 'C') || line[1] != SPACE)
		return (ft_putendl_fd("Erro: identificador de cor inválido", 2), 0);
	*id = line[0];
	return (1);
}

static int	validate_rgb_format(const char *line)
{
	int	i;
	int	comma;
	int	expecting_number;

	i = 2;
	comma = 0;
	expecting_number = 1;
	while (line[i])
	{
		if (line[i] == SPACE || line[i] == NEWLINE)
			i++;
		else if (ft_isdigit(line[i]))
		{
			expecting_number = 0;
			while (ft_isdigit(line[i]))
				i++;
		}
		else if (line[i] == COMMA)
		{
			if (expecting_number)
				return (0);
			comma++;
			expecting_number = 1;
			i++;
		}
		else
			return (0);
	}
	if (expecting_number || comma != 2)
		return (0);
	return (1);
}

static int	validate_rgb_values(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j] == SPACE || rgb[i][j] == NEWLINE)
			j++;
		if (!ft_isdigit(rgb[i][j]))
			return (0);
		while (ft_isdigit(rgb[i][j]))
			j++;
		while (rgb[i][j] == SPACE || rgb[i][j] == NEWLINE)
			j++;
		if (rgb[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	set_color(t_game *game, char id, int r, int g, int b)
{
	if (id == 'F')
	{
		if (game->f_set)
			return (ft_putendl_fd("Erro: F já definido", 2), 0);
		game->floor_color = (r << 16) | (g << 8) | b;
		game->f_set = 1;
	}
	else
	{
		if (game->c_set)
			return (ft_putendl_fd("Erro: C já definido", 2), 0);
		game->ceiling_color = (r << 16) | (g << 8) | b;
		game->c_set = 1;
	}
	return (1);
}

int	parse_color(const char *line, t_game *game)
{
	char	**rgb;
	int		r, g, b;
	char	id;

	if (!validate_identifier(line, &id))
		return (0);
	if (!validate_rgb_format(line))
		return (ft_putendl_fd("Erro: formato RGB inválido", 2), 0);
	rgb = ft_split(line + 2, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_putendl_fd("Erro: formato RGB inválido", 2), 0);
	if (!validate_rgb_values(rgb))
		return (free_split(rgb), ft_putendl_fd("Erro: valor RGB inválido", 2), 0);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(rgb), ft_putendl_fd("Erro: RGB fora do intervalo (0-255)", 2), 0);
	if (!set_color(game, id, r, g, b))
		return (free_split(rgb), 0);
	free_split(rgb);
	return (1);
}
