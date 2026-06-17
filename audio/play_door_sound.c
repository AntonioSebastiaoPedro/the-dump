#include "../includes/thedump.h"

void	play_door_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->door_sound)
	{
		channel = BASS_SampleGetChannel(cub->door_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}