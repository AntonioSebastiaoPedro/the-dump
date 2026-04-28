/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 21:04:43 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/28 02:25:09 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

int	load_single_texture(t_cub *cub, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		ft_putendl_fd("Error\nNão foi possível carregar alguma textura", 2);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	return (1);
}

int	load_weapon_textures(t_cub *cub)
{
	int		state;
	int		frame;
	//char	paths[WEAPON_SHOT][WEAPON_FRAMES];

 	char *paths[WEAPON_STATES][WEAPON_FRAMES] = {
        {
            "assets/weapon/idle/idle1.xpm",
			NULL, NULL, NULL, NULL, NULL,
        },
        {
            "assets/weapon/move/move1.xpm",
            "assets/weapon/move/move2.xpm",
            "assets/weapon/move/move3.xpm",
            "assets/weapon/move/move4.xpm",
            "assets/weapon/move/move5.xpm",
            "assets/weapon/move/move6.xpm",
        },
        {
            "assets/weapon/shot/shot1.xpm",
            "assets/weapon/shot/shot2.xpm",
            "assets/weapon/shot/shot3.xpm",
            "assets/weapon/shot/shot4.xpm",
            //"assets/weapon/shot/shot5.xpm",
            //"assets/weapon/shot/shot6.xpm",
        },
    };

	state = 0;
	while (state < WEAPON_STATES)
	{
		frame = 0;
		while (frame < WEAPON_FRAMES)
		{
			if (paths[state][frame] == NULL)
			{
				frame++;
				continue ;
			}
			if (!load_single_texture(cub, &cub->weapon.frames[state][frame], paths[state][frame]))
			{
				ft_putendl_fd("Error\nNão foi possível carregar alguma textura", 2);
				return (0);
			}
			frame++;
		}
		state++;
	}
	cub->weapon.state = WEAPON_IDLE;
	cub->weapon.current_frame = 0;
	cub->weapon.frame_timer = 0;
	set_weapon_state(&cub->weapon, WEAPON_IDLE);
	return (1);
}

int	load_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->textures->no, cub->config->no))
		return (0);
	if (!load_single_texture(cub, &cub->textures->so, cub->config->so))
		return (0);
	if (!load_single_texture(cub, &cub->textures->we, cub->config->we))
		return (0);
	if (!load_single_texture(cub, &cub->textures->ea, cub->config->ea))
		return (0);
	if (!load_weapon_textures(cub))
		return (0);
	return (1);
}
