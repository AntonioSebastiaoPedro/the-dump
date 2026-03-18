/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-17 11:09:15 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

int	main(int ac, char **av)
{
    t_game  game;

    ft_memset(&game, 0, sizeof(game));
    parser(ac, av, &game);


    printf("\nValor main: %s\n", game.no);
    printf("\nValor main: %s\n", game.so);
    printf("\nValor main: %s\n", game.ea);
    printf("\nValor main: %s\n", game.we);
    printf("\nValor main: %d\n", game.floor_color);
    printf("\nValor main: %d\n", game.ceiling_color);

}

