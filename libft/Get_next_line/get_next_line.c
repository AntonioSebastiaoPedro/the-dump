/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:07:35 by paulcard          #+#    #+#             */
/*   Updated: 2025/07/22 15:46:18 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_fill_line(int fd, char *stash, char *buffer)
{
	char	*tmp;
	int		bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*ft_set_line(char *line_buffer)
{
	char	*stash;
	size_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	stash = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (!stash)
		return (NULL);
	line_buffer[i + 1] = 0;
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	line = ft_fill_line(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash = ft_set_line(line);
	return (line);
}
