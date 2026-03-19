/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-19 12:21:38 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-19 12:21:38 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

char    *ft_strcpy(char *dest, const char *src)
{
    int i;

    if (!src || !dest)
        return (NULL);
    i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}