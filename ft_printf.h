/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:17:49 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/11 12:09:37 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

int			ft_printf(const char *str, ...);

size_t		ft_strclen(const char *str, const char *condstr);

int			ft_putnstr(const char *str, size_t n, int count);

int			ft_putnbr_base(void *ptr, char *base, int sign, int count);

int			ft_putptr(unsigned long ptr, int count);

int			in(char c, const char *str);

const char	*ft_findspef(const char *str, const char *spef);
#endif
