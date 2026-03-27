/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:18:20 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 16:43:33 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

t_player	*init_player(t_cub *cub)
{
	if (!cub->player || !cub->player->dir)
		return (NULL);
	set_dir_vectors(cub->player);
	return (cub->player);
}
