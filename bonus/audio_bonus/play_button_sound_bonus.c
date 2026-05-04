/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_button_sound_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:03:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 17:03:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	play_button_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->button_sound)
	{
		channel = BASS_SampleGetChannel(cub->button_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}
