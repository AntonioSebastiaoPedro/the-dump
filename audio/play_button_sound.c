#include "../includes/cub.h"

void	play_button_sound(t_cub *cub)
{
	unsigned int	channel;

	if (cub->button_sound)
	{
		channel = BASS_SampleGetChannel(cub->button_sound, FALSE);
		BASS_ChannelPlay(channel, FALSE);
	}
}