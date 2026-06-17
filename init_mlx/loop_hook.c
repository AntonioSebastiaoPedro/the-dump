#include "../includes/thedump.h"

typedef struct s_win_list
{
	Window		window;
}				t_win_list;

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
}				t_xvar;

int	is_window_focused(t_cub *cub)
{
	Window	focused_win;
	t_xvar	*xvar;
	int		revert;

	xvar = (t_xvar *)cub->mlx->mlx;
	XGetInputFocus(xvar->display, &focused_win, &revert);
	return (focused_win == xvar->win_list->window);
}

double ft_get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

/* ========== PERFORMANCE OPTIMIZATION ========== */
static void	check_render_dirty(t_cub *cub)
{
	double	angle_diff;
	double	pos_diff;

	angle_diff = fabs(cub->player->dir_x - cub->last_player_angle);
	pos_diff = fabs(cub->player->pos_x - cub->last_player_x) + 
			   fabs(cub->player->pos_y - cub->last_player_y);
	
	if (angle_diff > 0.001 || pos_diff > 0.001)
	{
		cub->render_dirty = true;
		cub->last_player_angle = cub->player->dir_x;
		cub->last_player_x = cub->player->pos_x;
		cub->last_player_y = cub->player->pos_y;
	}
	else
	{
		cub->render_dirty = false;
	}
}

static int	should_skip_frame(t_cub *cub)
{
	double	elapsed;
	double	current;

	current = ft_get_time();
	elapsed = current - cub->frame_start_time;
	
	if (elapsed < FRAME_TIME)
	{
		usleep((FRAME_TIME - elapsed) * 1000000);
		return (1);
	}
	cub->frame_start_time = current;
	return (0);
}
/* ============================================== */


int	loop_hook(t_cub *cub)
{
	char *time = NULL;

	if (cub->state == LOADING)
	{
		loading_render(cub);
		pthread_mutex_lock(&cub->loader.mutex);
		if (cub->loader.done)
		{
			pthread_mutex_unlock(&cub->loader.mutex);
			pthread_join(cub->loader.thread, NULL);
			cub->state = MENU;
			init_menu(cub);
		}
		else
			pthread_mutex_unlock(&cub->loader.mutex);
	}
	else if (cub->state == MENU)
	{
		poll_joystick(cub);
		update_menu(cub);
		render_menu(cub);
	}
	else if (cub->state == ABOUT)
	{
		poll_joystick(cub);
		render_about(cub);
	}
	else if (cub->state == GAME)
	{
		/* Frame rate limiting */
		if (should_skip_frame(cub))
			return (0);

		poll_joystick(cub);
		if (!cub->game_paused)
		{
			update_player(cub);
			update_doors(cub);
			update_enemies(cub);
			update_items(cub);
			update_weapon(cub);
		}

		int offset = 0;
		cub->current_time = ft_get_time();
		if (cub->last_time == 0.0)
		{
			cub->last_time = cub->current_time;
			return (1);
		}
		cub->delta_time = cub->current_time - cub->last_time;
		cub->last_time = cub->current_time;
		cub->t_elapsed_time += cub->delta_time;
		cub->elapsed_time += cub->delta_time;

		if (cub->delta_time <= 0.0)
			cub->delta_time = 0.0;
		if (cub->delta_time > 1.0 / 60.0)
			cub->delta_time = 1.0 / 60.0;
		
		/* Check if we need to render (dirty flag) */
		check_render_dirty(cub);
		render(cub);
		
		/* =========== RENDER TIMER ============== */
		time = ft_itoa((int)roundf(cub->elapsed_time));
		draw_empty_rect(cub, (t_vec){(WIDTH/2)-70,13.5}, (t_vec){140,40}, WHITE);
		if (roundf(cub->elapsed_time) >= 10)
			offset = 5;
		draw_string_graphics(cub, WIDTH / 2 - offset, HEIGHT / 2 - 480, time, WHITE);
		free(time);
		/* ========================================= */
		if (cub->player_hp <= 0)
			cub->state = GAME_OVER;
		else if (check_level_completion(cub))
			cub->state = LEVEL_TRANSITION;
		else if (!is_window_focused(cub))
			cub->state = MENU;
	}
	else if (cub->state == LEVEL_TRANSITION)
	{
		/*
		 * Those 2 lines is to prevent current time being too big if
		 * the player stays in between Dead or Level trans,
		 * so when goes back to game mode the elapsed times wouldnt just jump values.
		 */
		cub->current_time = ft_get_time(); 
		cub->last_time = cub->current_time;

		poll_joystick(cub);
		render_transition_screen(cub);

		if (cub->keys[KEY_ENTER])
		{
			cub->keys[KEY_ENTER] = 0;
			load_next_level(cub);
		}
	}
	else if (cub->state == GAME_OVER)
	{
		cub->current_time = ft_get_time();
		cub->last_time = cub->current_time;
		poll_joystick(cub);
		render_game_over(cub);
		if (cub->keys[ESC])
		{
			cub->keys[ESC] = 0;
			restart_game(cub);
			cub->last_time = 0.0;
			cub->elapsed_time = 0.0;
		}
	}
	else if (cub->state == VICTORY)
	{
		cub->current_time = ft_get_time();
		cub->last_time = cub->current_time;
		poll_joystick(cub);
		render_victory_screen(cub);
		if (cub->keys[KEY_ENTER])
		{
			cub->keys[KEY_ENTER] = 0;
			restart_game(cub);
		}
		else if (cub->keys[ESC])
		{
			cub->keys[ESC] = 0;
			ft_close(cub);
		}
	}
	return (0);
}
