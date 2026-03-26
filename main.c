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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	main(int ac, char **av)
{
    t_mlx   mlx;
    t_game  game;

    ft_memset(&game, 0, sizeof(game));
    memset(&mlx, 0, sizeof(t_mlx));
    if (!parser(ac, av, &game))
        return(free_game(&game), 1);
    init_mlx(&mlx);
    render(&mlx);
    mlx_loop(&mlx);
    free_game(&game);
    return (0);
}

