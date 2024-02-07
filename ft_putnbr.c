/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 05:02:58 by olmohame          #+#    #+#             */
/*   Updated: 2024/01/05 05:03:04 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	ft_put_unsigned(unsigned long nbr, size_t radix, char *base)
{
	ssize_t	ret;
	ssize_t	mod;

	if (nbr < radix)
		return (write(1, &base[nbr], 1));
	else
	{
		mod = ft_put_unsigned(nbr / radix, radix, base);
		if (mod != -1)
			ret = ft_put_unsigned(nbr % radix, radix, base);
	}
	if (mod == -1 || ret == -1)
		return (-1);
	return (ret + mod);
}

static int	ft_put_signed(long nbr, int base_radix, char *base)
{
	int	ret;
	int	mod;
	int	sign;

	sign = 0;
	if (base_radix == 10 && nbr < 0)
	{
		sign = write(1, "-", 1);
		nbr = nbr * -1;
	}
	if (sign != -1 && nbr < base_radix)
		return (sign + write(1, &base[nbr], 1));
	else
	{
		if (sign != -1)
			mod = ft_put_signed(nbr / base_radix, base_radix, base);
		if (sign != -1 && mod != -1)
			ret = ft_put_signed(nbr % base_radix, base_radix, base);
	}
	if (sign == -1 || mod == -1 || ret == -1)
		return (-1);
	return (ret + mod + sign);
}

int	ft_putnbr_base(void *ptr, char *base, int sign, int count)
{
	int	base_radix;
	int	ret;

	base_radix = ft_strclen(base, "\0");
	if (!sign)
		ret = ft_put_unsigned((unsigned long)ptr, base_radix, base);
	else
		ret = ft_put_signed((long)ptr, base_radix, base);
	if (ret == -1)
		ret = -1 * (count + 1);
	return (ret);
}

int	ft_putptr(unsigned long nbr, int count)
{
	int	pre;
	int	ret;

	pre = write(1, "0x", 2);
	if (pre != -1)
		ret = ft_put_unsigned(nbr, 16, "0123456789abcdef");
	if (pre == -1 || ret == -1)
		return (-1 *(count + 1));
	return (pre + ret);
}
