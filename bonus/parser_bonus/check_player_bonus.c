#include "../includes_bonus/cub_bonus.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static	void	set_player_position(char **map, t_cub *cub, int x, int y)
{
	cub->player->pos_x = x + 0.5;
	cub->player->pos_y = y + 0.5;
	cub->player->dir = map[y][x];
}

int	check_player_help(char **map, t_cub *cub)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	cub->player->dir = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				count++;
				if (count == 1)
					set_player_position(map, cub, j, i);
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	check_player(char **map, t_cub *cub)
{
	int	count;

	count = check_player_help(map, cub);
	if (count == 0)
		return (ft_putendl_fd("Error\nJogador ausente", 2), 0);
	if (count > 1)
		return (ft_putendl_fd("Error\nMúltiplos jogadores", 2), 0);
	return (1);
}