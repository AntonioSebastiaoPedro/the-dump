/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:58:04 by aamandio          #+#    #+#             */
/*   Updated: 2026/05/04 23:04:28 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

char	ft_delim(const char *s)
{
	int	i;

	if (!s)
		return ('\0');
	i = 0;
	while (s[i])
	{
		if (ft_strchr(" \t\v\r\f", s[i]))
			return (s[i]);
		i++;
	}
	return ('\0');
}
