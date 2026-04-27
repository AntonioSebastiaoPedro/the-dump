/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:58:04 by aamandio          #+#    #+#             */
/*   Updated: 2026/04/17 15:33:58 by paulcard         ###   ########.fr       */
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
