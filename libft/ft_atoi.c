#include "libft.h"

static int	ft_check_overflow(long long res, int digit, int sign)
{
	if (sign == 1)
	{
		if (res > INT_MAX / 10
			|| (res == INT_MAX / 10 && digit > INT_MAX % 10))
			return (INT_MAX);
	}
	else
	{
		if (res > (-(long long)INT_MIN) / 10
			|| (res == (-(long long)INT_MIN) / 10 && digit > (-(INT_MIN % 10))))
			return (INT_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	t_atoi	atoi;

	atoi.i = 0;
	atoi.sign = 1;
	atoi.result = 0;
	if (!str)
		return (0);
	while (str[atoi.i] == 32 || (str[atoi.i] >= 9 && str[atoi.i] <= 13))
		atoi.i++;
	if (str[atoi.i] == '-' || str[atoi.i] == '+')
	{
		if (str[atoi.i] == '-')
			atoi.sign = -1;
		atoi.i++;
	}
	while (ft_isdigit(str[atoi.i]))
	{
		atoi.digit = str[atoi.i] - '0';
		atoi.check = ft_check_overflow(atoi.result, atoi.digit, atoi.sign);
		if (atoi.check != 0)
			return (atoi.check);
		atoi.result = atoi.result * 10 + atoi.digit;
		atoi.i++;
	}
	return ((int)(atoi.sign * atoi.result));
}