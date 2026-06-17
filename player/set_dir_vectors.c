#include "../includes/thedump.h"

static void	set_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

static void	set_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}

static void	set_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}

static void	set_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void	set_dir_vectors(t_player *player)
{
	char	c;

	c = player->dir;
	if (c == 'N')
		set_north(player);
	else if (c == 'S')
		set_south(player);
	else if (c == 'E')
		set_east(player);
	else if (c == 'W')
		set_west(player);
}