#include "../includes/thedump.h"

void	init_campaign(t_cub *cub, int ac, char **av)
{
	static char *campaign[] = {
		"maps/level1.cub",
		"maps/level2.cub",
		"maps/level3.cub",
		"maps/level4.cub",
		"maps/level5.cub",
		"maps/level6.cub",
		"maps/level7.cub",
		"maps/level8.cub",
		"maps/level9.cub",
		"maps/level10.cub",
		NULL
	};

	if (ac == 1)
	{
		cub->level_mgr.is_campaign = 1;
		cub->level_mgr.campaign_maps = campaign;
		cub->level_mgr.total_levels = 10;
	}
	else
	{
		cub->level_mgr.is_campaign = 0;
		cub->level_mgr.campaign_maps = &av[1];
		cub->level_mgr.total_levels = 1;
	}
	cub->level_mgr.current_level_idx = 0;
	cub->level_mgr.level_completed = 0;
}

int	check_level_completion(t_cub *cub)
{
	int	i;
	int	has_boss;
	int	bosses_alive;
	int	enemies_alive;

	has_boss = 0;
	bosses_alive = 0;
	enemies_alive = 0;
	i = 0;
	while (i < cub->enemy_count)
	{
		if (cub->enemies[i].is_boss)
		{
			has_boss = 1;
			if (cub->enemies[i].alive)
				bosses_alive++;
		}
		else if (cub->enemies[i].alive)
			enemies_alive++;
		i++;
	}
	if (has_boss)
		return (bosses_alive == 0);
	return (enemies_alive == 0);
}

void	restart_game(t_cub *cub)
{
	cub->level_mgr.current_level_idx = -1; // so load_next_level sets it to 0
	load_next_level(cub);
}

void	restart_level(t_cub *cub)
{
	cub->level_mgr.current_level_idx--; // decrement so load_next_level restores it to current
	load_next_level(cub);
}

void	load_next_level(t_cub *cub)
{
	char	*next_map;

	cub->level_mgr.current_level_idx++;
	if (cub->level_mgr.current_level_idx >= cub->level_mgr.total_levels)
	{
		stop_back_sound(cub);
		play_level_done_sound(cub);
		cub->state = VICTORY;
		return ;
	}
	resume_back_sound(cub);
	next_map = cub->level_mgr.campaign_maps[cub->level_mgr.current_level_idx];

	// Free current level resources safely
	if (cub->enemies)
	{
		free_enemies(cub);
		free_enemy_textures(cub);
	}
	free_textures(cub);
	if (cub->door)
	{
		free(cub->door);
		cub->door = NULL;
		cub->n_door = 0;
	}
	if (cub->map && cub->map->grid)
	{
		clear_map(cub);
		clear_config(cub);
		cub->textures->skybox.img = NULL;
	}

	// Reset Player state (not the pointer)
	if (cub->player)
	{
		cub->player->dir = 0;
		cub->player->pos_x = 0;
		cub->player->pos_y = 0;
	}
	cub->has_blue_key = false;
	cub->gold_buff_timer = 0;
	cub->max_gold_buff_timer = 0;

	// Load new map
	if (!parse_map_into_cub(cub, next_map))
	{
		ft_putendl_fd("Error\nFalha ao carregar proximo mapa", 2);
		cub->state = GAME_OVER;
		return ;
	}
	if (!load_textures(cub))
	{
		cub->state = GAME_OVER;
		return ;
	}
	init_player(cub);
	init_doors(cub);
	init_enemies(cub);
	if (cub->enemies && !load_enemy_textures(cub))
	{
		cub->state = GAME_OVER;
		return ;
	}
	cub->player_hp = PLAYER_MAX_HP;
	player_add_ammo(cub);
	cub->state = GAME;
}
