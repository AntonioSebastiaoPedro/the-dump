#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dest = (char *) malloc(len * sizeof(char));
	if (dest == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}