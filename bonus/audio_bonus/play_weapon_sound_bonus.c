#include "../includes_bonus/cub_bonus.h"

/* Retrieves a playback channel for the sample and plays it */
void	play_weapon_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->current_weapon && cub->current_weapon->shoot_sound)
	{
		channel = BASS_SampleGetChannel(cub->current_weapon->shoot_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}