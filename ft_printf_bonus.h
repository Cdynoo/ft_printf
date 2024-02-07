/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 10:36:08 by olmohame          #+#    #+#             */
/*   Updated: 2023/12/23 10:37:53 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

int			ft_printf(const char *str, ...);

int			validate(va_list *ptr, const char *start, \
							const char *last, int count);

int			match_and_print(va_list *ptr, char spef, long *flags, int count);

int			ft_putchar_f(char c, long *flags, int count);

int			ft_putstr(char *str, long *flags, int count);

int			ft_put_cor_str(const char *str, const char *last, \
							long *flags, int count);

int			ft_putnstr(const char *str, size_t n, int count);

int			ft_base_signed(long nbr, char *base, long *flags, int count);

int			ft_base_unsigned(unsigned long nbr, char *base, \
							long *flags, int count);

int			ft_putptr(unsigned long ptr, long *flags, int count);

int			print_prefix(long *flags, int signed_pos, int hex);

int			ft_form(int len, int signed_pos, int hex, long *flags);

size_t		ft_strclen(const char *str, const char *condstr);

int			ft_writenchars(long n, char *c);

int			in(char c, const char *str);

const char	*ft_findspef(const char *str, const char *spef);

int			ft_isdigit(int c);

void		*ft_memset(void *ptr, int c, size_t len);
#endif
