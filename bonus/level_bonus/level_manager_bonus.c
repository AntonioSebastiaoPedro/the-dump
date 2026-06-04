#include "../includes_bonus/cub_bonus.h"

void	init_campaign(t_cub *cub, int ac, char **av)
{
	static char *campaign[] = {
		"maps/enemy_test.cub",
		"maps/level1.cub",
		"maps/level2.cub",
		"maps/boss.cub",
		NULL
	};

	if (ac == 1)
	{
		cub->level_mgr.is_campaign = 1;
		cub->level_mgr.campaign_maps = campaign;
		cub->level_mgr.total_levels = 4;
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
	int	boss_dead;
	int	enemies_alive;

	has_boss = 0;
	boss_dead = 0;
	enemies_alive = 0;
	i = 0;
	while (i < cub->enemy_count)
	{
		if (cub->enemies[i].is_boss)
		{
			has_boss = 1;
			if (!cub->enemies[i].alive)
				boss_dead = 1;
		}
		else if (cub->enemies[i].alive)
			enemies_alive++;
		i++;
	}
	if (has_boss)
		return (boss_dead);
	return (enemies_alive == 0);
}

void	restart_game(t_cub *cub)
{
	cub->level_mgr.current_level_idx = -1; // so load_next_level sets it to 0
	load_next_level(cub);
}

void	load_next_level(t_cub *cub)
{
	char	*next_map;

	cub->level_mgr.current_level_idx++;
	if (cub->level_mgr.current_level_idx >= cub->level_mgr.total_levels)
	{
		play_level_done_sound(cub);
		cub->state = VICTORY;
		return ;
	}
	play_level_done_sound(cub);
	next_map = cub->level_mgr.campaign_maps[cub->level_mgr.current_level_idx];

	// Free current level resources safely
	free_enemies(cub);
	free_enemy_textures(cub);
	free_textures(cub);
	if (cub->door)
	{
		free(cub->door);
		cub->door = NULL;
		cub->n_door = 0;
	}
	clear_map(cub);
	clear_config(cub);

	// Reset Player state (not the pointer)
	if (cub->player)
		cub->player->dir = 0;

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
	if (!load_enemy_textures(cub))
	{
		cub->state = GAME_OVER;
		return ;
	}
	cub->player_hp = PLAYER_MAX_HP;
	cub->state = GAME;
}
