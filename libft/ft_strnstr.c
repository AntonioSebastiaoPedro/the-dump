#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!big && len == 0)
		return (NULL);
	if (!little)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	j = 0;
	while (j < len && big[j])
	{
		i = 0;
		while ((j + i < len) && big[j + i] && big[j + i] == little[i])
			i++;
		if (little[i] == '\0')
			return ((char *)&big[j]);
		j++;
	}
	return (NULL);
}