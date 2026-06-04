/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_audio_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:47:10 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 09:47:36 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	BASS_Free();
}
