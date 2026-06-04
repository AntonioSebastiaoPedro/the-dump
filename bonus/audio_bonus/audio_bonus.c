/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:56:46 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 16:56:52 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

/* Use SampleLoad for sound effects:
	 * param 5 (max) is 3 for up to 3 overlapping sounds.
*/
/* 4 is BASS_SAMPLE_LOOP */

static HSAMPLE	load_sound(char *path, int max, int flags)
{
	HSAMPLE	sound;

	sound = BASS_SampleLoad(FALSE, path, 0, 0, max, flags);
	if (!sound)
	{
		ft_putstr_fd("Warning: Failed to load ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	return (sound);
}

static HCHANNEL	init_channel(HSAMPLE sound, bool autoplay)
{
	HCHANNEL	channel;

	if (!sound)
		return (0);
	channel = BASS_SampleGetChannel(sound, FALSE);
	if (autoplay)
		BASS_ChannelPlay(channel, FALSE);
	return (channel);
}

static bool	init_bass(void)
{
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
	{
		ft_putstr_fd("Error\nBASS initialization failed\n", 2);
		return (false);
	}
	return (true);
}

bool	init_audio(t_cub *cub)
{
	if (!init_bass())
		return (false);
	cub->weapons[WEAPON_REVOLVER].shoot_sound = load_sound(
			"assets/sounds/weapon/revolver.mp3", 3, 0);
	cub->weapons[WEAPON_MACHINEGUN].shoot_sound = load_sound(
			"assets/sounds/atkmachinegun.mp3", 3, 0);
	cub->weapons[WEAPON_GATLING].shoot_sound = load_sound(
			"assets/sounds/atkgatling.mp3", 3, 0);
	cub->run_sound = load_sound(
			"assets/sounds/run/run.mp3", 1, 4);
	cub->door_sound = load_sound(
			"assets/sounds/door/door_1.mp3", 3, 0);
	cub->back_sound = load_sound(
			"assets/sounds/back3.mp3", 1, 4);
	cub->button_sound = load_sound(
			"assets/sounds/button.mp3", 3, 0);
	cub->run_channel = init_channel(cub->run_sound, false);
	cub->back_channel = init_channel(cub->back_sound, true);
	return (true);
}
