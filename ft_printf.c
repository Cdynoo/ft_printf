/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:27:50 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/08 03:21:22 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_write_char(char c, int count)
{
	if (write(1, &c, 1) == -1)
		return (-1 * (count + 1));
	return (1);
}

static int	ft_write_str(char *str, int count)
{
	if (!str)
		return (ft_putnstr("(null)", 6, count));
	else
		return (ft_putnstr(str, ft_strclen(str, "\0"), count));
}

static int	match_and_print(va_list *ptr, char spef, int count)
{
	if (spef == 'c')
		return (ft_write_char(va_arg(*ptr, int), count));
	if (spef == 's')
		return (ft_write_str(va_arg(*ptr, char *), count));
	if (spef == 'p')
		return (ft_putptr((unsigned long)va_arg(*ptr, void *), count));
	if (spef == 'd' || spef == 'i')
		return (ft_putnbr_base((void *)(long) \
					va_arg(*ptr, int), "0123456789", 1, count));
	if (spef == 'u')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), "0123456789", 0, count));
	if (spef == 'x')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), "0123456789abcdef", 0, count));
	if (spef == 'X')
		return (ft_putnbr_base((void *)(unsigned long) \
					va_arg(*ptr, unsigned int), "0123456789ABCDEF", 0, count));
	else
		return (ft_write_char('%', count));
}

static int	validate(va_list *p, const char *start, const char *last, int count)
{
	int			len;
	const char	*spef;

	spef = "cspdiuxX%";
	if (!*start)
		return (0);
	if (!in(*start, spef))
	{
		len = ft_strclen(start, last);
		if (last)
			len++;
		return (ft_putnstr(start, len, count));
	}
	else
		return (match_and_print(p, *start, count));
}

int	ft_printf(const char *str, ...)
{
	int			count;
	const char	*start;
	const char	*last;
	va_list		ptr;

	if (!str)
		return (0);
	count = 0;
	va_start(ptr, str);
	while (*str)
	{
		start = ft_findspef(str, "%");
		count += ft_putnstr(str, ft_strclen(str, start), count);
		str += ft_strclen(str, start) + 1;
		if (count == -1 || !start)
			break ;
		last = ft_findspef(str, "cspdiuxX%");
		count += validate(&ptr, start + 1, last, count);
		str = last + 1;
		if (count == -1 || !last)
			break ;
	}
	va_end(ptr);
	return (count);
}
