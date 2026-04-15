/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:20:54 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/15 10:27:10 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static bool	is_delimiter(char c, const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (c == delim[i])
			return (true);
		i++;
	}
	return (false);
}

static int	ft_count_words(const char *str, const char *delim)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_delimiter(str[i], delim))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && !is_delimiter(str[i], delim))
			i++;
	}
	return (count);
}

static int	ft_count_char(const char *s, const char *delim, int start)
{
	int	len;

	len = 0;
	while (s[start + len] != '\0' && !is_delimiter(s[start + len], delim))
		len++;
	return (len);
}

char	**ft_split_new(const char *s, const char *delim)
{
	char	**box;
	int		i;
	int		start;
	int		words;

	if (!s || !delim)
		return (NULL);
	words = ft_count_words(s, delim);
	box = (char **)malloc((words + 1) * sizeof(char *));
	if (!box)
		return (NULL);
	i = 0;
	start = 0;
	while (i < words)
	{
		while (s[start] && is_delimiter(s[start], delim))
			start++;
		box[i] = ft_substr(s, start, ft_count_char(s, delim, start));
		if (!box[i])
		{
			free_split(box);
			return (NULL);
		}
		start += ft_count_char(s, delim, start);
		i++;
	}
	box[i] = NULL;
	return (box);
}
