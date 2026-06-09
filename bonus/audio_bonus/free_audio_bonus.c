#include "../includes_bonus/cub_bonus.h"

void	free_audio(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < WEAPON_COUNT)
	{
		if (cub->weapons[i].shoot_sound)
			BASS_SampleFree(cub->weapons[i].shoot_sound);
		i++;
	}
	if (cub->run_sound)
		BASS_SampleFree(cub->run_sound);
	if (cub->door_sound)
		BASS_SampleFree(cub->door_sound);
	if (cub->back_sound)
		BASS_SampleFree(cub->back_sound);
	if (cub->button_sound)
		BASS_SampleFree(cub->button_sound);
	if (cub->level_done_sound)
		BASS_SampleFree(cub->level_done_sound);
	if (cub->player_death_sound)
		BASS_SampleFree(cub->player_death_sound);
	if (cub->enemy_death_sound)
		BASS_SampleFree(cub->enemy_death_sound);
	BASS_Free();
}