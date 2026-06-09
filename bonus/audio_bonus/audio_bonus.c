/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:56:46 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/04 18:27:15 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

/* Use SampleLoad for sound effects:
	 * param 5 (max) is 3 for up to 3 overlapping sounds.
*/
/* 4 is BASS_SAMPLE_LOOP */

static HSAMPLE	load_sound(t_cub *cub, char *path, int max, int flags)
{
	HSAMPLE	sound;

	sound = BASS_SampleLoad(FALSE, path, 0, 0, max, flags);
	if (!sound)
	{
		ft_putstr_fd("Warning: Failed to load ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	increment_loader(cub);
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

// som ambiente back3.mp3

bool	init_audio(t_cub *cub)
{
	if (!init_bass())
		return (false);
	cub->weapons[WEAPON_REVOLVER].shoot_sound = load_sound(cub,
			"assets/sounds/weapon/revolver.mp3", 3, 0);
	cub->weapons[WEAPON_RIFLE].shoot_sound = load_sound(cub,
			"assets/sounds/atkmachinegun.mp3", 3, 0);
	cub->weapons[WEAPON_PLASMA].shoot_sound = load_sound(cub,
			"assets/sounds/atkgatling.mp3", 3, 0);
	cub->run_sound = load_sound(cub,
			"assets/sounds/run/run.mp3", 1, 4);
	cub->door_sound = load_sound(cub,
			"assets/sounds/door/door_1.mp3", 3, 0);
	cub->back_sound = load_sound(cub,
			"assets/sounds/xfunkie.mp3", 1, 4);
	cub->button_sound = load_sound(cub,
			"assets/sounds/button.mp3", 3, 0);
	cub->level_done_sound = load_sound(cub,
			"assets/sounds/leveldone.mp3", 1, 0);
	cub->player_death_sound = load_sound(cub,
			"assets/sounds/playerdeath.mp3", 1, 0);
	cub->enemy_death_sound = load_sound(cub,
			"assets/sounds/soldier/deathscream1.mp3", 1, 4);
	cub->run_channel = init_channel(cub->run_sound, false);
	cub->back_channel = init_channel(cub->back_sound, true);
	return (true);
}

void	play_level_done_sound(t_cub *cub)
{
	init_channel(cub->level_done_sound, true);
}

void	play_player_death_sound(t_cub *cub)
{
	init_channel(cub->player_death_sound, true);
}

void	play_enemy_death_sound(t_cub *cub)
{
	init_channel(cub->enemy_death_sound, true);
}
