#include "../includes_bonus/cub_bonus.h"

static void	remove_newline(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			return ;
		}
		i++;
	}
}

char	**copy_map(char **lines, int map_start, int height)
{
	char	**map;
	int		i;

	map = malloc((height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = ft_strdup(lines[map_start + i]);
		if (!map[i])
			return (free_map(map, i), NULL);
		remove_newline(map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}