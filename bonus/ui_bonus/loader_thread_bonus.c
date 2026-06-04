/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_thread_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:35:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/04 13:35:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	increment_loader(t_cub *cub)
{
	pthread_mutex_lock(&cub->loader.mutex);
	if (cub->loader.total_items > 0)
	{
		cub->loader.items_loaded++;
		cub->loading.progress = (cub->loader.items_loaded * 100)
			/ cub->loader.total_items;
		if (cub->loading.progress > 100)
			cub->loading.progress = 100;
	}
	pthread_mutex_unlock(&cub->loader.mutex);
}

void	*load_assets_thread(void *arg)
{
	t_cub	*cub;

	cub = (t_cub *)arg;
	
	init_player(cub);
	init_audio(cub);
	init_joystick(cub);
	load_textures(cub);
	init_enemies(cub);
	load_enemy_textures(cub);

	pthread_mutex_lock(&cub->loader.mutex);
	cub->loader.done = 1;
	cub->loading.progress = 100;
	pthread_mutex_unlock(&cub->loader.mutex);
	
	return (NULL);
}

void	start_loader_thread(t_cub *cub)
{
	if (pthread_create(&cub->loader.thread, NULL, load_assets_thread, cub) != 0)
	{
		ft_putendl_fd("Error\nCould not create loader thread", 2);
		ft_close(cub);
	}
}
