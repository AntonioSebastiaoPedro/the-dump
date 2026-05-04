/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_floor_ceiling_texture_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:20:40 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 11:21:27 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

bool	load_floor_ceiling_texture(t_cub *cub)
{
	if (cub->config->f_tex)
	{
		if (!load_single_texture(cub, &cub->textures->floor,
				cub->config->f_tex))
			return (0);
	}
	if (cub->config->c_tex)
	{
		if (!load_single_texture(cub, &cub->textures->ceiling,
				cub->config->c_tex))
			return (0);
	}
	return (1);
}
