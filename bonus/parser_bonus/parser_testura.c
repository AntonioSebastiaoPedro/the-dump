/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_testura.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:03:13 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/07 11:10:51 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

static char	*trim_path(char **parts)
{
	char	*tmp;

	tmp = ft_strtrim(parts[1], " \n\r\t");
	free(parts[1]);
	parts[1] = tmp;
	return (tmp);
}

static int	open_texture(const char *path, char *dir, char **parts)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Erro: Caminho da Textura ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(" invalida", 2);
		free_split(parts);
		return (-1);
	}
	close(fd);
	return (fd);
}

static int	set_texture(char **dest, char **parts, char *dir)
{
	char	*path;

	if (*dest)
	{
		ft_putstr_fd("Erro: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(" já definido", 2);
		free_split(parts);
		return (0);
	}
	path = trim_path(parts);
	if (open_texture(path, dir, parts) < 0)
		return (0);
	*dest = ft_strdup(path);
	return (1);
}

int	parse_texture(const char *line, t_cub *cub)
{
	char	**parts;
	int		ret;

	parts = ft_split(line, ft_delim(line));
	if (!parts || !parts[0] || !parts[1] || parts[2])
	{
		ft_putendl_fd("Erro: Textura Invalida", 2);
		free_split(parts);
		return (0);
	}
	if (ft_strcmp(parts[0], "NO") == 0)
		ret = set_texture(&cub->config->no, parts, "NO");
	else if (ft_strcmp(parts[0], "SO") == 0)
		ret = set_texture(&cub->config->so, parts, "SO");
	else if (ft_strcmp(parts[0], "WE") == 0)
		ret = set_texture(&cub->config->we, parts, "WE");
	else if (ft_strcmp(parts[0], "EA") == 0)
		ret = set_texture(&cub->config->ea, parts, "EA");
	else
	{
		ret = (ft_putendl_fd("Erro: Textura nao existe", 2), free_split(parts), 0);
	}
	if (ret)
		free_split(parts);
	return (ret);
}
