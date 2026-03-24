/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/24 15:24:42 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

int	main(int ac, char **av)
{
    t_game  game;

    ft_memset(&game, 0, sizeof(game));
    if (!parser(ac, av, &game))
    {
        free_game(&game);
        return (1);
    }


    printf("\nValor main: %s\n", game.no);
    printf("\nValor main: %s\n", game.so);
    printf("\nValor main: %s\n", game.ea);
    printf("\nValor main: %s\n", game.we);
    printf("\nValor main: %d\n", game.floor_color);
    printf("\nValor main: %d\n", game.ceiling_color);
    printf("\nValor main: %d\n", game.map_height);
    printf("\nValor main: %d\n", game.map_width);
    print_map(game.map);
    free_game(&game);
    return (0);
}

