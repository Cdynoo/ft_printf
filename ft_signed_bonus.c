/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signed_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:37:22 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:37:29 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_putnbr(long nbr, long base_radix, char *base)
{
	int	ret;
	int	mod;
	int	sign;

	sign = 0;
	if (base_radix == 10 && nbr < 0)
		nbr = nbr * -1;
	if (nbr < base_radix)
		return (write(1, &base[nbr], 1));
	else
	{
		mod = ft_putnbr(nbr / base_radix, base_radix, base);
		if (mod != -1)
			ret = ft_putnbr(nbr % base_radix, base_radix, base);
	}
	if (mod == -1 || ret == -1)
		return (-1);
	return (ret + mod);
}

static int	countnbr(long nbr, long base_radix, char *base)
{
	int	mod;

	if (base_radix == 10 && nbr < 0)
		return (countnbr(-nbr, base_radix, base));
	if (nbr < base_radix)
		return (1);
	else
	{
		mod = countnbr(nbr / base_radix, base_radix, base);
		return (mod + countnbr(nbr % base_radix, base_radix, base));
	}
}

int	ft_base_signed(long nbr, char *base, long *flags, int count)
{
	int	base_radix;
	int	ret;
	int	ret_f;
	int	ret_s;

	ret = 0;
	base_radix = ft_strclen(base, "\0");
	flags[9] = nbr == 0;
	ret_f = ft_form(countnbr(nbr, base_radix, base), nbr >= 0, 0, flags);
	if (!((nbr == 0) && (flags[6] + flags[8]) == 1) && ret_f != -1)
		ret = ft_putnbr(nbr, base_radix, base);
	if (ret_f != -1 && ret != -1)
		ret_s = ft_writenchars(flags[0], " ");
	if (ret_f == -1 || ret == -1 || ret_s == -1)
		return (-1 * (count + 1));
	return (ret_f + ret + ret_s);
}
