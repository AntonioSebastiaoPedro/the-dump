#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	tam_substr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		tam_substr = ft_strlen(s) - start;
	else
		tam_substr = len;
	substr = (char *)malloc((tam_substr + 1) * sizeof(char));
	i = 0;
	while (i < tam_substr && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[tam_substr] = '\0';
	return (substr);
}