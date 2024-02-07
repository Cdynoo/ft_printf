/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:38:10 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:38:14 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static ssize_t	put_un_nbr(unsigned long nbr, size_t base_radix, char *base)
{
	ssize_t	ret;
	ssize_t	mod;

	if (nbr < base_radix)
		return (write(1, &base[nbr], 1));
	else
	{
		mod = put_un_nbr(nbr / base_radix, base_radix, base);
		if (mod != -1)
			ret = put_un_nbr(nbr % base_radix, base_radix, base);
	}
	if (mod == -1 || ret == -1)
		return (-1);
	return (ret + mod);
}

static int	count_un_nbr(unsigned long nbr, size_t base_radix, char *base)
{
	int	mod;

	if (base_radix == 10 && nbr < 0)
		return (count_un_nbr(-nbr, base_radix, base));
	if (nbr < base_radix)
		return (1);
	else
	{
		mod = count_un_nbr(nbr / base_radix, base_radix, base);
		return (mod + count_un_nbr(nbr % base_radix, base_radix, base));
	}
}

int	ft_base_unsigned(unsigned long nbr, char *base, long *flags, int count)
{
	int	base_radix;
	int	ret;
	int	ret_f;
	int	ret_s;

	ret = 0;
	base_radix = ft_strclen(base, "\0");
	flags[9] = nbr == 0;
	ret_f = ft_form(count_un_nbr(nbr, base_radix, base), nbr >= 0, \
	(base_radix == 16) && nbr != 0, flags);
	if (!((nbr == 0) && (flags[6] + flags[8]) == 1) && ret_f != -1)
		ret = put_un_nbr(nbr, base_radix, base);
	if (ret_f != -1 && ret != -1)
		ret_s = ft_writenchars(flags[0], " ");
	if (ret_f == -1 || ret == -1 || ret_s == -1)
		return (-1 * (count + 1));
	return (ret_f + ret + ret_s);
}

int	ft_putptr(unsigned long ptr, long *flags, int count)
{
	int	ret;
	int	i;

	i = 0;
	flags[0] = flags[0] - (count_un_nbr(ptr, 16, "0123456789abcdef") + 2);
	if (!(flags[1] + flags[5]))
		i = ft_writenchars(flags[0], " ");
	if (i == -1)
		return (-1 * (count + 1));
	if (write(1, "0x", 2) == -1)
		return (-1 * (count + 1));
	if (flags[1])
		i = ft_writenchars(flags[0], "0");
	if (i == -1)
		return (-1 * (count + 1));
	ret = put_un_nbr(ptr, 16, "0123456789abcdef");
	if (ret == -1)
		return (-1 * (count + 1));
	if (flags[5])
		i = ft_writenchars(flags[0], " ");
	if (i == -1)
		return (-1 * (count + 1));
	return (ret + i + 2);
}
