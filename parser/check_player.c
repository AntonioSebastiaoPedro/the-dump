/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 18:07:01 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 18:07:01 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

bool is_player(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int check_player(char **map, t_game *game)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    game->player_dir = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
            {
                count++;
                if (count == 1)
                {
                    game->player_x = j;
                    game->player_y = i;
                    game->player_dir = map[i][j];
                }
                map[i][j] = '0'; 
            }
            j++;
        }
        i++;
    }
    if (count == 0)
        return (ft_putendl_fd("Erro: jogador ausente", 2), 0);
    if (count > 1)
        return (ft_putendl_fd("Erro: múltiplos jogadores", 2), 0);
    return (1);
}
