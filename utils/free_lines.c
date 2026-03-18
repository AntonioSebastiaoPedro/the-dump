/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-18 12:06:33 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-18 12:06:33 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void    free_lines(char **lines)
{
    int i;

    if (!lines)
        return ;
    i = 0;
    while (lines[i])
    {
        free(lines[i]);
        i++;
    }
    free(lines);
}