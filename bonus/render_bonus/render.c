/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:15:23 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/28 00:43:22 by aamandio         ###   ########.fr       */
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

// Obtem a quantidade de frames tendo em conta a animacao
int	get_max_frames(int state)
{
	if (state == WEAPON_IDLE)
		return (1);
	else if (state == WEAPON_MOVE)
		return (WEAPON_FRAMES);
	else if (state == WEAPON_SHOT)
		return (WEAPON_FRAMES);
	return (0);
}

// Altera o tipo de animacao da arma
void	set_weapon_state(t_weapon *weapon, int new_state)
{
	if (weapon->state == new_state)
		return ;
	weapon->state = new_state;
	weapon->current_frame = 0;
	weapon->frame_timer = 0;
	if (new_state == WEAPON_IDLE)
		weapon->frame_delay = 15;
	else if (new_state == WEAPON_MOVE)
		weapon->frame_delay = 8;
	else if (new_state == WEAPON_SHOT)
		weapon->frame_delay = 4;
}

// Avanca para o proximo frame da animacao
void	update_frame(t_weapon *weapon)
{
	weapon->frame_timer++;
	if (weapon->frame_timer >= weapon->frame_delay)
	{
		weapon->frame_timer = 0;
		weapon->current_frame++;
	}
}

// Controlador de animacoes da arma
void	update_weapon(t_cub *cub)
{
	t_weapon	*weapon;
	int			max_frames;

	weapon = &cub->weapon;
	if (weapon->state == WEAPON_SHOT)
	{
		update_frame(weapon); // Experimentar trocar a ordem
		max_frames = get_max_frames(weapon->state);
		if (weapon->current_frame >= max_frames)
		{
			if (cub->player->is_moving)
				set_weapon_state(weapon, WEAPON_MOVE);
			else
				set_weapon_state(weapon, WEAPON_IDLE);
			}
		return ; // Se a animacao for de tiro, deixa-se terminar. Nao pode mudar...
	}
	if (cub->player->is_moving)
		set_weapon_state(weapon, WEAPON_MOVE);
	else
		set_weapon_state(weapon, WEAPON_IDLE);
	update_frame(weapon); // Experimentar trocar a ordem
	max_frames = get_max_frames(weapon->state);
	if (weapon->current_frame >= max_frames)
		weapon->current_frame = 0;
}

void	draw_weapon(t_cub *cub)
{
	(void)cub;
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
	update_weapon(cub);
	draw_weapon(cub);
	mlx_put_image_to_window(cub->mlx->mlx, cub->mlx->win, cub->mlx->img, 0, 0);
}
