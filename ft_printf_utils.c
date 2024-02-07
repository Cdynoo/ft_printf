/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:30:36 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/10 01:30:41 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strclen(const char *str, const char *condstr)
{
	size_t	str_len;
	char	cond;

	str_len = 0;
	if (!condstr)
		cond = '\0';
	else
		cond = *condstr;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

int	in(char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

const char	*ft_findspef(const char *str, const char *spef)
{
	while (*str)
	{
		if (in(*str, spef))
			return (str);
		str++;
	}
	return (0);
}

int	ft_putnstr(const char *str, size_t n, int count)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (*str && i < n)
		{
			if (write(1, str++, 1) == -1)
				return (-1 * (count + 1));
			i++;
		}
	}
	return (i);
}
