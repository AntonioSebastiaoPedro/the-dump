/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 10:28:32 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 10:28:32 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int ft_count_lines(int fd)
{
    char    *line;
    int     count;

    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        free(line);
        count++;
        line = get_next_line(fd);
    }
    return (count);
}