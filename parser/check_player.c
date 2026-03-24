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

int check_player(char **map)
{
    int	i;
    int	j;
    int	player_count;

    player_count = 0;
    i = 0;
    while (map[i])
    {
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				player_count++;
			j++;
		}
		i++;
    }
    if (player_count == 0)
        return (ft_putendl_fd("Erro: jogador ausente no mapa", 2), 0);
    if (player_count > 1)
        return (ft_putendl_fd("Erro: múltiplos jogadores no mapa", 2), 0);
    return (1);
}