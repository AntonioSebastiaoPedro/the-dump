/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:35:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/05/01 18:43:56 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

/* Use SampleLoad for sound effects:
	 * param 5 (max) is 3 for up to 3 overlapping sounds.
*/
void	init_audio(t_cub *cub)
{
	cub->weapon_sound = 0;
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
	{
		ft_putstr_fd("Error\nBASS initialization failed\n", 2);
		return ;
	}
	cub->weapon_sound = BASS_SampleLoad(FALSE,
			"assets/sounds/weapon/revolver.mp3", 0, 0, 3, 0);
	if (!cub->weapon_sound)
		ft_putstr_fd("Warning: Failed to load assets/sounds/weapon/revolver.mp3\n", 2);
	cub->run_sound = BASS_SampleLoad(FALSE,
			"assets/sounds/run/run.mp3", 0, 0, 1, 4); /* 4 is BASS_SAMPLE_LOOP */
	if (!cub->run_sound)
		ft_putstr_fd("Warning: Failed to load assets/sounds/run/run.mp3\n", 2);
	cub->door_sound = BASS_SampleLoad(FALSE,
			"assets/sounds/door/door_1.mp3", 0, 0, 3, 0);
	if (!cub->door_sound)
		ft_putstr_fd("Warning: Failed to load assets/sounds/door/door_1.mp3\n", 2);
	if (cub->run_sound)
		cub->run_channel = BASS_SampleGetChannel(cub->run_sound, FALSE);
	else
		cub->run_channel = 0;
}

/* Retrieves a playback channel for the sample and plays it */
void	play_weapon_sound(t_cub *cub)
{
	unsigned int channel;

	if (cub->weapon_sound)
	{
		channel = BASS_SampleGetChannel(cub->weapon_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}

void	play_door_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->door_sound)
	{
		channel = BASS_SampleGetChannel(cub->door_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}

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

void	free_audio(t_cub *cub)
{
	if (cub->weapon_sound)
		BASS_SampleFree(cub->weapon_sound);
	if (cub->run_sound)
		BASS_SampleFree(cub->run_sound);
	if (cub->door_sound)
		BASS_SampleFree(cub->door_sound);
	BASS_Free();
}
