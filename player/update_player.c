/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:48:35 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 14:00:34 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void	update_player(t_player *player, t_map *map, int  key)
{
	(void)map;
	(void)player;
	if (key == KEY_W)
		printf("Precionou W\n");
	else if (key == KEY_S)
		printf("Precionou S\n");
	else if (key == KEY_A)
		printf("Precionou A\n");
	else if (key == KEY_D)
		printf("Precionou D\n");
	else if (key == KEY_LEFT)
		printf("Precionou LEFT\n");
	else if (key == KEY_RIGHT)
		printf("Precionou RIGHT\n");
}
