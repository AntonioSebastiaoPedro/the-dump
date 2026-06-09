#include "../includes/cub.h"

char	ft_delim(const char *s)
{
	int	i;

	if (!s)
		return ('\0');
	i = 0;
	while (s[i])
	{
		if (ft_strchr(" \t\v\r\f", s[i]))
			return (s[i]);
		i++;
	}
	return ('\0');
}