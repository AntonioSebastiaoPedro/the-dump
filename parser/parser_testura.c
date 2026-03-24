/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_testura.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 14:03:13 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 14:03:13 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int parse_texture(const char *line, t_game *game)
{
	char	*tmp;
	int		fd_testura;
    char    **parts;

   parts = ft_split(line, SPACE);
   printf("Testura: %s\n", parts[0]);
   if (!parts || !parts[0] || !parts[1] || parts[2])
		return (ft_putendl_fd("Erro: Textura Invalida", 2), 0);
	if (ft_strcmp(parts[0], "NO") == 0)
	{
		if (game->no)
			return (ft_putendl_fd("Erro: NO já definido", 2), 0);
		tmp = ft_strtrim(parts[1], " \n\r\t");
		free(parts[1]);
		parts[1] = tmp;
		fd_testura = open(parts[1], O_RDONLY);
		printf("Caminho [%s]\n", parts[1]);
		if (fd_testura < 0)
			return (ft_putendl_fd("Erro: Caminho da Textura NO invalida", 2), 0);
		game->no = ft_strdup(parts[1]);
		close(fd_testura);
	}
	else if (ft_strcmp(parts[0], "SO") == 0)
	{
		if (game->so)
			return (ft_putendl_fd("Erro: SO já definido", 2), 0);
		tmp = ft_strtrim(parts[1], " \n\r\t");
		free(parts[1]);
		parts[1] = tmp;
		fd_testura = open(parts[1], O_RDONLY);
		printf("Caminho [%s]\n", parts[1]);
		if (fd_testura < 0)
			return (ft_putendl_fd("Erro: Caminho da Textura SO invalida", 2), 0);
		game->so = ft_strdup(parts[1]);
		close(fd_testura);
	}
	else if (ft_strcmp(parts[0], "WE") == 0)
	{
		if (game->we)
			return (ft_putendl_fd("Erro: WE já definido", 2), 0);
		tmp = ft_strtrim(parts[1], " \n\r\t");
		free(parts[1]);
		parts[1] = tmp;
		fd_testura = open(parts[1], O_RDONLY);
		printf("Caminho [%s]\n", parts[1]);
		if (fd_testura < 0)
			return (ft_putendl_fd("Erro: Caminho da Textura WE invalida", 2), 0);
		close(fd_testura);
		game->we = ft_strdup(parts[1]);
	}
	else if (ft_strcmp(parts[0], "EA") == 0)
	{
		if (game->ea)
			return (ft_putendl_fd("Erro: EA já definido", 2), 0);
		tmp = ft_strtrim(parts[1], " \n\r\t");
		free(parts[1]);
		parts[1] = tmp;
		fd_testura = open(parts[1], O_RDONLY);
		printf("Caminho [%s]\n", parts[1]);
		if (fd_testura < 0)
			return (ft_putendl_fd("Erro: Caminho da Textura EA invalida", 2), 0);
		close(fd_testura);
		game->ea = ft_strdup(parts[1]);
	}
	else
		return (ft_putendl_fd("Erro: Textura nao existe", 2), 0);
	free_split(parts);
   return (1);  
}