/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:15:00 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/07 15:15:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <stdarg.h>

static void ft_putnbr_fd_internal(int n, int fd, int *len)
{
    long nb = n;
    char c;

    if (nb < 0)
    {
        *len += write(fd, "-", 1);
        nb = -nb;
    }
    if (nb >= 10)
        ft_putnbr_fd_internal(nb / 10, fd, len);
    c = (nb % 10) + '0';
    *len += write(fd, &c, 1);
}

/**
 * @brief Simplified fprintf for file descriptors.
 * Supports %s, %d, %c, %%.
 */
int ft_fprintf_fd(int fd, const char *format, ...)
{
    va_list args;
    int i = 0;
    int len = 0;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            if (format[i] == 's')
            {
                char *s = va_arg(args, char *);
                if (!s) s = "(null)";
                len += write(fd, s, ft_strlen(s));
            }
            else if (format[i] == 'd')
                ft_putnbr_fd_internal(va_arg(args, int), fd, &len);
            else if (format[i] == 'c')
            {
                char c = (char)va_arg(args, int);
                len += write(fd, &c, 1);
            }
            else if (format[i] == '%')
                len += write(fd, "%", 1);
        }
        else
            len += write(fd, &format[i], 1);
        i++;
    }
    va_end(args);
    return (len);
}

static void ft_putnbr_buf(int n, char *buf, int *pos)
{
    long nb = n;

    if (nb < 0)
    {
        buf[(*pos)++] = '-';
        nb = -nb;
    }
    if (nb >= 10)
        ft_putnbr_buf(nb / 10, buf, pos);
    buf[(*pos)++] = (nb % 10) + '0';
}

/**
 * @brief Simplified sprintf for internal buffer formatting.
 * Supports %s, %d, %c, %%.
 */
int ft_sprintf(char *str, const char *format, ...)
{
    va_list args;
    int i = 0;
    int pos = 0;

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1])
        {
            i++;
            if (format[i] == 's')
            {
                char *s = va_arg(args, char *);
                if (!s) s = "(null)";
                while (*s) str[pos++] = *s++;
            }
            else if (format[i] == 'd')
                ft_putnbr_buf(va_arg(args, int), str, &pos);
            else if (format[i] == 'c')
                str[pos++] = (char)va_arg(args, int);
            else if (format[i] == '%')
                str[pos++] = '%';
        }
        else
            str[pos++] = format[i];
        i++;
    }
    str[pos] = '\0';
    va_end(args);
    return (pos);
}
