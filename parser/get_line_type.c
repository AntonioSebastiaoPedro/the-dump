#include "../includes/cub.h"

t_line_type	get_line_type(const char *line)
{
	if (!line || !line[0])
		return (EMPTY);
	while (*line == SPACE || *line == TAB)
		line++;
	if (*line == '\0' || *line == NEWLINE)
		return (EMPTY);
	if ((line[0] == 'N' && line[1] == 'O')
		|| (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E')
		|| (line[0] == 'E' && line[1] == 'A'))
	{
		if (line[2] == SPACE || line[2] == TAB || line[2] == NEWLINE)
			return (TEXTURE);
		return (INVALID);
	}
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (line[1] == SPACE || line[1] == NEWLINE || line[1] == TAB)
			return (COLOR);
		return (INVALID);
	}
	if (ft_strncmp(line, "SKY", 3) == 0)
	{
		if (line[3] == SPACE || line[3] == NEWLINE || line[3] == TAB)
			return (COLOR);
		return (INVALID);
	}
	if (line[0] == '0' || line[0] == '1' || line[0] == SPACE
		|| line[0] == 'N' || line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
		return (MAP);
	return (INVALID);
}