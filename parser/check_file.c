/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 09:10:51 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 09:10:51 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void	ft_check_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nUso: ./cub3D <map.cub>\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	ft_check_file(char *name)
{
    char	*filename;
	char	*extension;

	filename = ft_strrchr(name, '/');
	if (filename)
		filename++;
	else
		filename = name;
	extension = ft_strrchr(filename, '.');
	if (extension)
	{
		if (extension != filename && ft_strcmp(extension, ".cub") == 0)
			return (1);
	}
	return (0);
}

int	ft_open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nAo Abrir o ficheiro\n", 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void    ft_validate_file(int ac, char **av)
{
	ft_check_args(ac);
	if (!ft_check_file(av[1]))
	{
		ft_putstr_fd("Error\nFicheiro inválido. Precisa de .cub\n", 2);
		exit(EXIT_FAILURE);
	}
}
