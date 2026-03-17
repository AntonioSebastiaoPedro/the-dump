/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 20:04:40 by paulcard          #+#    #+#             */
/*   Updated: 2025/06/23 09:48:46 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_fillstr(char *str, long n, int len)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		str[0] = '-';
		sign = 1;
		n = -n;
	}
	str[len] = '\0';
	while (len > sign)
	{
		str[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_num_len(n);
	str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_fillstr(str, nb, len);
	return (str);
}
