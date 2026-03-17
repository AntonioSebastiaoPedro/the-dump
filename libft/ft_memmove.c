/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:42:06 by paulcard          #+#    #+#             */
/*   Updated: 2025/06/23 15:51:11 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	ft_copy_front(unsigned char *d, unsigned char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
}

static void	ft_copy_back(unsigned char *d, unsigned char *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest || !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s || n == 0)
		return (d);
	if (d > s && d < s + n)
	{
		ft_copy_back(d, s, n);
	}
	else
	{
		ft_copy_front(d, s, n);
	}
	return (d);
}
