#include "libft.h"
#include <stdarg.h>

static void	ft_putnbr_buf_len(int n, char *buf, int *pos)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		buf[(*pos)++] = '-';
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_buf_len(nb / 10, buf, pos);
	buf[(*pos)++] = (nb % 10) + '0';
}

static void	ft_hnd_fmt_buf(const char format, va_list args, char *str, int *pos)
{
	char	*s;
	char	c;

	if (format == 's')
	{
		s = va_arg(args, char *);
		if (!s)
			s = "(null)";
		while (*s)
			str[(*pos)++] = *s++;
	}
	else if (format == 'd' || format == 'i')
		ft_putnbr_buf_len(va_arg(args, int), str, pos);
	else if (format == 'c')
	{
		c = (char)va_arg(args, int);
		str[(*pos)++] = c;
	}
	else if (format == '%')
		str[(*pos)++] = '%';
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			ft_hnd_fmt_buf(format[i], args, str, &pos);
		}
		else
			str[pos++] = format[i];
		i++;
	}
	str[pos] = '\0';
	va_end(args);
	return (pos);
}