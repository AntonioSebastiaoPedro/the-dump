#include "../includes/thedump.h"
#include "../includes/macros.h"
#include <pthread.h>

/*
** ===== UPDATE THREAD WORKER =====
**
** Runs game-logic updates at TARGET_FPS on a background thread so they don't
** block the main render loop.  render() is intentionally NOT called here —
** it must only run on the main thread that owns the X11/mlx context.
**
** All state written here (player pos, enemy pos, etc.) is read by the render
** thread only after wait_raycast_threads() returns, so there is no data race
** provided the update thread finishes before the next start_raycast_threads().
** The mutex guards the shared game state during the update window.
*/
static void	*update_worker(void *arg)
{
	t_update_thread	*upd;
	double			frame_time;
	double			last_update;
	double			current_time;

	upd = (t_update_thread *)arg;
	last_update = ft_get_time();
	while (upd->active)
	{
		current_time = ft_get_time();
		frame_time = current_time - last_update;
		if (frame_time >= (1.0 / TARGET_FPS))
		{
			pthread_mutex_lock(&upd->mutex);
			if (!upd->cub->game_paused)
			{
				update_player(upd->cub);
				update_doors(upd->cub);
				update_enemies(upd->cub);
				update_items(upd->cub);
				update_projectiles(upd->cub);
				update_weapon(upd->cub);
			}
			pthread_mutex_unlock(&upd->mutex);
			last_update = current_time;
		}
		else
		{
			/* Yield CPU until the next update window */
			usleep(500);
		}
	}
	return (NULL);
}

/* ===== INITIALIZE UPDATE THREAD ===== */
t_update_thread	*init_update_thread(t_cub *cub)
{
	t_update_thread	*upd;

	upd = ft_calloc(1, sizeof(t_update_thread));
	if (!upd)
		return (NULL);
	upd->cub = cub;
	upd->active = 1;
	if (pthread_mutex_init(&upd->mutex, NULL) != 0)
		return (free(upd), NULL);
	if (pthread_create(&upd->thread, NULL, update_worker, upd) != 0)
	{
		ft_fprintf_fd(2, "Error creating update thread\n");
		pthread_mutex_destroy(&upd->mutex);
		return (free(upd), NULL);
	}
	return (upd);
}

/* ===== CLEANUP UPDATE THREAD ===== */
void	cleanup_update_thread(t_update_thread *upd)
{
	if (!upd)
		return ;
	upd->active = 0;
	pthread_join(upd->thread, NULL);
	pthread_mutex_destroy(&upd->mutex);
	free(upd);
}
