/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_weapon_sound_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:43:02 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 09:43:40 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

/* Retrieves a playback channel for the sample and plays it */
void	play_weapon_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->weapon_sound)
	{
		channel = BASS_SampleGetChannel(cub->weapon_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}
