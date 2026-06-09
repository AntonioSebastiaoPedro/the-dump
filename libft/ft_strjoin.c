#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newtam;
	size_t	i;
	size_t	j;
	size_t	total;

	if (!s1 || !s2)
		return (NULL);
	total = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	newtam = (char *) malloc(total * sizeof(char));
	if (newtam == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		newtam[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		newtam[j++] = s2[i++];
	}
	newtam[j] = '\0';
	return (newtam);
}