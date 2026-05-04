/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_sound_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:45:51 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 09:46:15 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	play_run_sound(t_cub *cub)
{
	if (cub->run_channel)
	{
		if (BASS_ChannelIsActive(cub->run_channel) != 1)
			BASS_ChannelPlay(cub->run_channel, FALSE);
	}
}

void	stop_run_sound(t_cub *cub)
{
	if (cub->run_channel)
	{
		if (BASS_ChannelIsActive(cub->run_channel) == 1)
			BASS_ChannelPause(cub->run_channel);
	}
}
