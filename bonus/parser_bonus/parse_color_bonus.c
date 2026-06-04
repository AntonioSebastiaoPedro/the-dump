/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:04:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 23:05:58 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static int	validate_identifier(const char *line, char *id)
{
	if (!line)
		return (0);
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (!ft_isspace(line[1]))
			return (ft_putendl_fd("Error\nIdentificador de cor inválido", 2), 0);
		*id = line[0];
		return (1);
	}
	if (ft_strncmp(line, "SKY", 3) == 0 && ft_isspace(line[3]))
	{
		*id = 'S';
		return (1);
	}
	return (ft_putendl_fd("Error\nIdentificador de cor inválido", 2), 0);
}

static int	validate_rgb_values(char **rgb)
{
	int	i;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (ft_isspace(rgb[i][j]))
			j++;
		if (!ft_isdigit(rgb[i][j]))
			return (0);
		while (ft_isdigit(rgb[i][j]))
			j++;
		while (ft_isspace(rgb[i][j]))
			j++;
		if (rgb[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	set_color(t_cub *cub, char id, t_rgb rgb)
{
	if (id == 'F')
	{
		if (cub->config->floor_color != -1)
			return (ft_putendl_fd("Error\nF já definido", 2), 0);
		cub->config->floor_color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
		cub->floor_color = cub->config->floor_color;
	}
	else
	{
		if (cub->config->ceiling_color != -1)
			return (ft_putendl_fd("Error\nC já definido", 2), 0);
		cub->config->ceiling_color = (rgb.r << 16) | (rgb.g << 8) | rgb.b;
		cub->ceiling_color = cub->config->ceiling_color;
	}
	return (1);
}

static int	parse_fc_texture(const char *line, char id, t_cub *cub)
{
	char	**parts;
	int		ret;

	parts = ft_split_new(line, " \t\n\r");
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		if (parts)
			free_split(parts);
		ft_putendl_fd("Error\nTextura Invalida", 2);
		return (0);
	}
	if (id == 'F')
		ret = set_cub_texture(&cub->config->f_tex, parts, "F");
	else
		ret = set_cub_texture(&cub->config->c_tex, parts, "C");
	if (ret)
		free_split(parts);
	return (ret);
}

int	parse_color(const char *line, t_cub *cub)
{
	char	**rgb;
	t_rgb	trgb;
	char	id;

	if (!validate_identifier(line, &id))
		return (0);
	if (!ft_strchr(line, ',') || id == 'S')
		return (parse_fc_texture(line, id == 'S' ? 'C' : id, cub));
	if (!validate_rgb_format(line))
		return (ft_putendl_fd("Error\nFormato RGB inválido", 2), 0);
	rgb = ft_split_new(line + 2, ",");
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (ft_putendl_fd("Error\nFormato RGB inválido", 2), 0);
	if (!validate_rgb_values(rgb))
		return (free_split(rgb), ft_putendl_fd(VALOR, 2), 0);
	trgb.r = ft_atoi(rgb[0]);
	trgb.g = ft_atoi(rgb[1]);
	trgb.b = ft_atoi(rgb[2]);
	if (trgb.r < 0 || trgb.r > 255 || trgb.g < 0
		|| trgb.g > 255 || trgb.b < 0 || trgb.b > 255)
		return (free_split(rgb), ft_putendl_fd(FORA, 2), 0);
	if (!set_color(cub, id, trgb))
		return (free_split(rgb), 0);
	free_split(rgb);
	return (1);
}
