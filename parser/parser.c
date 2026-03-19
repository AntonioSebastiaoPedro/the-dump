/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 12:28:44 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 12:28:44 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int parser(int ac, char **av, t_game *game)
{
    t_line_type type;
    int         i;
    char        **lines;
    int         map_start;

    i = 0;
    map_start = -1;
	ft_validate_file(ac, av);
    lines = read_file(av[1]);
    while (lines[i] != NULL)
    {
        type = get_line_type(lines[i]);
        if (type == TEXTURE)
        {
             if (parse_texture(lines[i], game) == 0)
                return (0);
        }
        else if (type == COLOR)
        {
            if (parse_color(lines[i], game) == 0)
                return (0);
        }
        else if (type == MAP)
        {
            if (map_start == -1)
                map_start = i;
            break;
        }
        else if (type == INVALID && lines[i][0] != '\0')
        {
            ft_putendl_fd("Mapa invalido", 2);
            return (0);
        }
        i++;
    }

    if (map_start == -1)
    {
        ft_putendl_fd("Ficheiro Nao encontrado no mapa", 2);
        return (0);
    }
    if (parse_map(lines, map_start ,game) == 0)
        return 0;
    return (1);
}