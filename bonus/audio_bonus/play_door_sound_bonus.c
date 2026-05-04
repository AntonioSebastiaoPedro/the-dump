/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_door_sound_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:44:02 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 09:44:35 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	play_door_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->door_sound)
	{
		channel = BASS_SampleGetChannel(cub->door_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}
