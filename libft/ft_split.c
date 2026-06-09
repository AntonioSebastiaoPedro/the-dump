#include "libft.h"
#include <stdio.h>

static int	ft_count_words(const char *str, char del)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == del && str[i] != '\0')
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != del && str[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_count_char(const char *s, char c, int start)
{
	int	end;

	end = 0;
	while (s[start + end] != c && s[start + end] != '\0')
		end++;
	return (end);
}

static void	free_split(char **box)
{
	int	i;

	i = 0;
	while (box[i])
	{
		free(box[i]);
		i++;
	}
	free(box);
}

char	**ft_split(const char *s, char c)
{
	char	**box;
	int		i;
	int		start;

	box = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!box)
		return (NULL);
	i = 0;
	start = 0;
	while (i < ft_count_words(s, c))
	{
		while (s[start] == c && s[start] != '\0')
			start++;
		box[i] = ft_substr(s, start, ft_count_char(s, c, start));
		if (!box[i])
		{
			free_split(box);
			return (NULL);
		}
		start += ft_count_char(s, c, start);
		i++;
	}
	box[ft_count_words(s, c)] = NULL;
	return (box);
}