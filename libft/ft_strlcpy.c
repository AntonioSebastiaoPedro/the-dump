#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (i < n - 1 && src[i])
	{
		dest[i] = (char)src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}