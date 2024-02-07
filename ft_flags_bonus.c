/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:36:44 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:37:35 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	detect_flow(long num, int dig)
{
	if (num > INT_MAX / 10)
		return (1);
	else if (num * 10 >= (INT_MAX - dig))
		return (1);
	return (0);
}

static int	read_num(const char *start, long *field)
{
	int	i;

	i = 0;
	*field = 0;
	while (start[i] && ft_isdigit(start[i]))
	{
		if (detect_flow(*field, start[i] - '0'))
		{
			*field = -1;
			while (start[i] && ft_isdigit(start[i]))
				i++;
			break ;
		}
		else
			*field = *field * 10 + start[i++] - '0';
	}
	return (i);
}

static int	store_flags(long *flags, va_list *ptr, const char *c)
{
	if (*c == '*')
		flags[0] = (long)va_arg(*ptr, int);
	else if (*c == '0')
		flags[1] = 1;
	else if (*c == '#')
		flags[2] = 1;
	else if (*c == ' ')
		flags[3] = 1;
	else if (*c == '+')
		flags[4] = 1;
	else if (*c == '-')
		flags[5] = 1;
	else if (*c == '.')
		flags[6] = 1;
	if (c[0] == '.' && c[1] && ft_isdigit(c[1]))
		return (1 + read_num(&c[1], &flags[8]));
	return (1);
}

static void	normalize_flags(long *flags, char c, const char *last)
{
	if (c == 'X')
		flags[7] = 1;
	if (c == 'c')
		flags[6] = 0;
	/*if (c == 'p')
	{
		flags[2] = 1;
		flags[9] = 2;
	}*/
	if (flags[5])
		flags[1] = 0;
	if (flags[6] && last && !in(*last, "csp"))
		flags[1] = 0;
}

int	validate(va_list *ptr, const char *start, const char *last, int count)
{
	int			i;
	long		fl[10];

	i = 0;
	ft_memset((void *)fl, 0, 10 * sizeof(long));
	while (in(start[i], "*0# +-.") || ft_isdigit(start[i]))
	{
		if (ft_isdigit(start[i]) && start[i] != '0')
			i += read_num(&start[i], &fl[0]);
		else
			i += store_flags(fl, ptr, &start[i]);
	}
	normalize_flags(fl, start[i], last);
	if (!start[i])
		return (0);
	if (fl[0] == -1 || fl[8] == -1)
		return (-1);
	else if (!in(start[i], "cspdiuxX%"))
		return (ft_put_cor_str(&start[i], last, fl, count));
	else
		return (match_and_print(ptr, start[i], fl, count));
}
