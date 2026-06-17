#include "../includes/cub.h"

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