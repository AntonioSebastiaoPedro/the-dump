#include "../includes/cub.h"
#include <pthread.h>

/*
** ===== RAYCAST THREAD WORKER (consumer) =====
**
** Each worker sleeps until the main thread signals a new frame (frame_id
** is incremented).  It then casts its assigned column slice and signals
** the main thread via done_cond once finished.
**
** No mutex is needed inside raycasting() because each worker owns a
** completely disjoint range of columns → no shared write targets.
*/
static void	*raycast_worker(void *arg)
{
	t_raycast_job	*job;
	t_thread_pool	*pool;
	t_ray			ray;
	int				last_frame;
	int				col;

	job = (t_raycast_job *)arg;
	pool = job->cub->raycast_pool;
	last_frame = 0;

	pthread_mutex_lock(&pool->work_mutex);
	while (pool->active)
	{
		/* Wait for a new frame to be signalled */
		while (pool->active && pool->frame_id == last_frame)
			pthread_cond_wait(&pool->work_cond, &pool->work_mutex);

		if (!pool->active)
			break ;

		last_frame = pool->frame_id;
		pthread_mutex_unlock(&pool->work_mutex);

		/* === Process assigned columns (no lock needed) === */
		col = job->start_col;
		while (col < job->end_col)
		{
			raycasting(col, &ray, job->cub);
			col++;
		}

		/* Signal completion */
		pthread_mutex_lock(&pool->work_mutex);
		pool->done_count++;
		if (pool->done_count == pool->num_threads)
			pthread_cond_signal(&pool->done_cond);
	}
	pthread_mutex_unlock(&pool->work_mutex);
	return (NULL);
}

/* ===== THREAD POOL INITIALIZATION ===== */
t_thread_pool	*init_raycast_pool(t_cub *cub)
{
	t_thread_pool	*pool;
	int				cols_per_thread;
	int				i;

	pool = ft_calloc(1, sizeof(t_thread_pool));
	if (!pool)
		return (NULL);
	pool->num_threads = NUM_THREADS;
	pool->num_cols = WIDTH;
	pool->active = 1;
	pool->frame_id = 0;
	pool->done_count = 0;
	pool->threads = ft_calloc(NUM_THREADS, sizeof(pthread_t));
	if (!pool->threads)
		return (free(pool), NULL);
	pool->jobs = ft_calloc(NUM_THREADS, sizeof(t_raycast_job));
	if (!pool->jobs)
		return (free(pool->threads), free(pool), NULL);
	if (pthread_mutex_init(&pool->work_mutex, NULL) != 0)
		return (free(pool->jobs), free(pool->threads), free(pool), NULL);
	if (pthread_cond_init(&pool->work_cond, NULL) != 0)
		return (pthread_mutex_destroy(&pool->work_mutex),
			free(pool->jobs), free(pool->threads), free(pool), NULL);
	if (pthread_cond_init(&pool->done_cond, NULL) != 0)
		return (pthread_cond_destroy(&pool->work_cond),
			pthread_mutex_destroy(&pool->work_mutex),
			free(pool->jobs), free(pool->threads), free(pool), NULL);
	cols_per_thread = WIDTH / NUM_THREADS;
	/* CRITICAL: assign pool to cub BEFORE creating threads.
	** Workers access cub->raycast_pool on startup — it must be set first. */
	cub->raycast_pool = pool;
	i = 0;
	while (i < NUM_THREADS)
	{
		pool->jobs[i].thread_id = i;
		pool->jobs[i].start_col = i * cols_per_thread;
		if (i == NUM_THREADS - 1)
			pool->jobs[i].end_col = WIDTH;
		else
			pool->jobs[i].end_col = (i + 1) * cols_per_thread;
		pool->jobs[i].cub = cub;
		if (pthread_create(&pool->threads[i], NULL,
				raycast_worker, &pool->jobs[i]) != 0)
		{
			ft_fprintf_fd(2, "Error creating raycasting thread %d\n", i);
			return (NULL);
		}
		i++;
	}
	return (pool);
}

/*
** ===== START (producer) =====
** Wakes all sleeping workers by bumping frame_id and broadcasting.
** Resets done_count so wait_raycast_threads knows when all are done.
*/
void	start_raycast_threads(t_cub *cub)
{
	t_thread_pool	*pool;

	pool = cub->raycast_pool;
	pthread_mutex_lock(&pool->work_mutex);
	pool->done_count = 0;
	pool->frame_id++;
	pthread_cond_broadcast(&pool->work_cond);
	pthread_mutex_unlock(&pool->work_mutex);
}

/*
** ===== WAIT (join-point) =====
** Blocks until every worker thread has finished its column slice for
** this frame.  Safe to proceed with minimap/HUD/mlx_put_image after this.
*/
void	wait_raycast_threads(t_cub *cub)
{
	t_thread_pool	*pool;

	pool = cub->raycast_pool;
	pthread_mutex_lock(&pool->work_mutex);
	while (pool->done_count < pool->num_threads)
		pthread_cond_wait(&pool->done_cond, &pool->work_mutex);
	pthread_mutex_unlock(&pool->work_mutex);
}

/* ===== THREAD POOL CLEANUP ===== */
void	cleanup_raycast_pool(t_thread_pool *pool)
{
	int	i;

	if (!pool)
		return ;
	/* Wake all threads so they can see active == 0 and exit */
	pthread_mutex_lock(&pool->work_mutex);
	pool->active = 0;
	pool->frame_id++;
	pthread_cond_broadcast(&pool->work_cond);
	pthread_mutex_unlock(&pool->work_mutex);
	i = 0;
	while (i < pool->num_threads)
	{
		pthread_join(pool->threads[i], NULL);
		i++;
	}
	pthread_cond_destroy(&pool->done_cond);
	pthread_cond_destroy(&pool->work_cond);
	pthread_mutex_destroy(&pool->work_mutex);
	free(pool->threads);
	free(pool->jobs);
	free(pool);
}
