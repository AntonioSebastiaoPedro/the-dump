#include "libft.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\r' || c == '\v');
}