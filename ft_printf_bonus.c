/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:27:50 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/10 00:02:16 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	match_and_print(va_list *ptr, char spef, long *flags, int count)
{
	if (spef == 'c')
		return (ft_putchar_f(va_arg(*ptr, int), flags, count));
	if (spef == 's')
		return (ft_putstr(va_arg(*ptr, char *), flags, count));
	if (spef == 'p')
		return (ft_putptr((unsigned long)va_arg(*ptr, void *), flags, count));
	if (spef == 'd' || spef == 'i')
		return (ft_base_signed((long) \
					va_arg(*ptr, int), "0123456789", flags, count));
	if (spef == 'u')
		return (ft_base_unsigned((unsigned long) \
					va_arg(*ptr, unsigned int), "0123456789", flags, count));
	if (spef == 'x')
		return (ft_base_unsigned((unsigned long) \
					va_arg(*ptr, unsigned int), \
					"0123456789abcdef", flags, count));
	if (spef == 'X')
		return (ft_base_unsigned((unsigned long) \
					va_arg(*ptr, unsigned int), \
					"0123456789ABCDEF", flags, count));
	else
		return (ft_putchar_f('%', flags, count));
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
