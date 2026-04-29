/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 10:25:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 11:40:09 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

static int	get_line_count(char *filename)
{
	int	fd;
	int	count;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\nAo Abrir o ficheiro", 2);
		return (-1);
	}
	count = ft_count_lines(fd);
	close(fd);
	if (count == 0)
		ft_putendl_fd("Error\nFile is empty", 2);
	return (count);
}

static char	**fill_lines(int fd, int count)
{
	char	**lines;
	int		i;

	lines = (char **)malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	lines[i] = get_next_line(fd);
	while (lines[i])
	{
		i++;
		lines[i] = get_next_line(fd);
	}
	lines[i] = NULL;
	return (lines);
}

char	**read_file(char *filename)
{
	int		fd;
	int		count;
	char	**lines;

	count = get_line_count(filename);
	if (count <= 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\nAo Abrir o ficheiro", 2);
		return (NULL);
	}
	lines = fill_lines(fd, count);
	close(fd);
	if (!lines)
		ft_putendl_fd("Error\nFalha a alocar Memoria", 2);
	return (lines);
}
