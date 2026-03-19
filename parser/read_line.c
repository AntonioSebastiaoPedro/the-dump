/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 10:25:24 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 10:25:24 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

char    **read_file(char *filename)
{
    int     i;
    int     fd;
    int     line_count;
    char    **lines;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return ((ft_putendl_fd("Erro: Ao Abrir o ficheiro", 2)), NULL);
    line_count = ft_count_lines(fd);
    if (line_count == 0)
        return (close(fd), ft_putendl_fd("Error: File is empty", 2), NULL);
    close(fd);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return ((ft_putstr_fd("Erro: Ao Abrir o ficheiro", 2)), NULL);
    lines = (char **)malloc(sizeof(char *) * (line_count + 1));
    if (!lines)
        return (ft_putendl_fd("Error: Falha a alocar Mempria", 2), close(fd), NULL);
    i = 0;
    lines[i] = get_next_line(fd);
    if (!lines[i])
    {
        //TODO: vai dar pau, Arranjar uma forma de liberar toda memoria
    }
    while (lines[i])
    {
        i++;
        lines[i] = get_next_line(fd);
    }
	lines[i] = NULL; 
    return (lines);
}
