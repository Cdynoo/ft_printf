/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:38:51 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:38:57 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static long	ft_min(long len, long *flags)
{
	if ((flags[8] + flags[6]) > 0 && flags[8] < len)
		return (flags[8]);
	return (len);
}

int	ft_writenchars(long n, char *c)
{
	int	i;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			if (write(1, c, 1) == -1)
				return (-1);
			i++;
		}
	}
	return (i);
}

int	ft_putstr(char *str, long *flags, int count)
{
	int		i;
	long	len;
	int		ret;

	if (!str)
		len = 6;
	else
		len = ft_strclen(str, "\0");
	i = 0;
	len = ft_min(len, flags);
	flags[0] -= len;
	if (flags[1])
		i = ft_writenchars(flags[0], "0");
	else if (!flags[5])
		i = ft_writenchars(flags[0], " ");
	if (i != -1 && !str)
		ret = ft_putnstr("(null)", len, count);
	else if (i != -1)
		ret = ft_putnstr(str, len, count);
	if (i != -1 && ret != -1 && flags[5])
		i = ft_writenchars(flags[0], " ");
	if (i == -1 || ret == -1)
		return (-1 * (count + 1));
	return (i + ret);
}

int	ft_put_cor_str(const char *str, const char *last, long *flags, int count)
{
	int	len;
	int	ret_c;
	int	ret_s;

	ret_c = ft_putchar_f(*str, flags, count);
	len = ft_strclen(++str, last) + 1;
	if (last && *last == '%')
		len--;
	if (ret_c != -1)
		ret_s = ft_putnstr(str, len, count);
	if (ret_c == -1 || ret_s == -1)
		return (-1 * (count + 1));
	return (ret_c + ret_s);
}

int	ft_putchar_f(char c, long *flags, int count)
{
	int	i;

	i = 0;
	flags[0]--;
	if (flags[1])
		i = ft_writenchars(flags[0], "0");
	else if (!flags[5])
		i = ft_writenchars(flags[0], " ");
	if (i == -1)
		return (-1);
	if (write(1, &c, 1) == -1)
		return (-1 * (count + 1));
	if (flags[5])
		i = ft_writenchars(flags[0], " ");
	if (i == -1)
		return (-1);
	return (i + 1);
}
