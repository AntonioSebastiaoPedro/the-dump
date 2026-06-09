#include "libft.h"
#include <stdarg.h>

static void	ft_putnbr_fd_len(int n, int fd, int *len)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		*len += write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd_len(nb / 10, fd, len);
	c = (nb % 10) + '0';
	*len += write(fd, &c, 1);
}

static void	ft_handle_format(const char format, va_list args, int fd, int *len)
{
	char	*s;
	char	c;

	if (format == 's')
	{
		s = va_arg(args, char *);
		if (!s)
			s = "(null)";
		*len += write(fd, s, ft_strlen(s));
	}
	else if (format == 'd' || format == 'i')
		ft_putnbr_fd_len(va_arg(args, int), fd, len);
	else if (format == 'c')
	{
		c = (char)va_arg(args, int);
		*len += write(fd, &c, 1);
	}
	else if (format == '%')
		*len += write(fd, "%", 1);
}

int	ft_fprintf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			ft_handle_format(format[i], args, fd, &len);
		}
		else
			len += write(fd, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}