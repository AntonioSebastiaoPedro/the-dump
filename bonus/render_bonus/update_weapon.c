/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:21:53 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/29 14:53:35 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

// Obtem a quantidade de frames tendo em conta a animacao
static int	get_max_frames(int state)
{
	if (state == WEAPON_IDLE)
		return (1);
	else if (state == WEAPON_MOVE)
		return (7);
	else if (state == WEAPON_SHOT)
		return (9);
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
		weapon->frame_delay = 4;
	else if (new_state == WEAPON_SHOT)
		weapon->frame_delay = 6;
}

// Avanca para o proximo frame da animacao
static void	update_frame(t_weapon *weapon)
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

	weapon = &cub->weapon;
	if (weapon->state == WEAPON_SHOT)
	{
		update_frame(weapon);
		if (weapon->current_frame >= get_max_frames(weapon->state))
		{
			if (cub->player->is_moving)
				set_weapon_state(weapon, WEAPON_MOVE);
			else
				set_weapon_state(weapon, WEAPON_IDLE);
		}
		return ;
	}
	if (cub->player->is_moving)
		set_weapon_state(weapon, WEAPON_MOVE);
	else
		set_weapon_state(weapon, WEAPON_IDLE);
	update_frame(weapon);
	if (weapon->current_frame >= get_max_frames(weapon->state))
		weapon->current_frame = 0;
}
