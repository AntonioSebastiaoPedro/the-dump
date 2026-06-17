#include "../includes/thedump.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (ft_putendl_fd("Line do Mapa invalido", 2), 0);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_line_map(char *line)
{
	int	i;

	if (!line)
		return (ft_putendl_fd("Line do Mapa invalido", 2), 0);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEWDKMBOGHP\t \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}