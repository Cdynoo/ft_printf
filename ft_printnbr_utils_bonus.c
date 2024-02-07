/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:39:24 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:39:27 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (len-- > 0)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (ptr);
}

static long	ft_max(long len, long *flags)
{
	if (flags[8] > len)
		return (flags[8]);
	return (len);
}

int	print_prefix(long *flags, int signed_pos, int hex)
{
	char	*prefix;
	int		i;

	i = 0;
	if (flags[3] > 0)
		prefix = " ";
	if (flags[4] > 0)
		prefix = "+";
	if (!signed_pos)
		prefix = "-";
	if (hex && flags[7])
		prefix = "0X";
	else if (hex && !flags[7])
		prefix = "0x";
	if ((flags[3] + flags[4]) > 0 || !signed_pos || flags[2] * hex)
	{
		if (write(1, prefix, 1 + flags[2] * hex) == -1)
			return (-1);
		i = (1 + flags[2] * hex);
	}
	return (i);
}

int	ft_form(int len, int signed_pos, int hex, long *flags)
{
	int	i;
	int	ret;
	int	ret_p;

	i = 0;
	ret_p = 0;
	flags[0] -= (ft_max(len, flags) + (flags[3] || flags[4]) * signed_pos \
	+ !signed_pos + flags[2] * hex * 2 - flags[6] * flags[9] * !flags[8]);
	if (!(flags[1] + flags[5]))
		i = ft_writenchars(flags[0], " ");
	if (i != -1)
		ret = print_prefix(flags, signed_pos, hex);
	if (i != -1 && ret != -1 && flags[1])
		i = ft_writenchars(flags[0], "0");
	if (!flags[5])
		flags[0] = 0;
	if (i != -1 && ret != -1 && flags[6])
		ret_p = ft_writenchars(flags[8] - len, "0");
	if (i == -1 || ret == -1 || ret_p == -1)
		return (-1);
	return (i + ret + ret_p);
}
