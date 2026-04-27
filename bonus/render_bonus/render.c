/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/27 19:06:09 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

unsigned int	get_texture_pixel_color(t_texture texture, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(texture.addr + (y * texture.line_len)
		+ (x * (texture.bpp / 8)));
	return (color);
}

int	load_weapon_frames(t_cub *cub)
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
            "assets/weapon/shot/shot5.xpm",
            "assets/weapon/shot/shot6.xpm",
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
			if (!load_single_texture(cub, &cub->weapon.frames[state][frame],
				paths[state][frame]))
					return (0); // liberar em caso de erro...
			frame++;
		}
		state++;
	}

	cub->weapon.state = WEAPON_IDLE;
	cub->weapon.current_frame = 0;
	cub->weapon.frame_timer = 0;
	return (1);
}

void	draw_weapon(t_cub *cub)
{
	load_weapon_frames(cub);
}

void	render(t_cub *cub)
{
	unsigned int	*pos;
	int				i;
	t_ray			ray;

	i = 0;
	pos = (unsigned int *)cub->mlx->addr;
	while (i < WIDTH * HEIGHT)
		*(pos + i++) = BLACK;
	i = 0;
	while (i < WIDTH)
		raycasting(i++, &ray, cub);
	draw_minimap(cub);
	draw_weapon(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
