/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:23:51 by cheller           #+#    #+#             */
/*   Updated: 2019/03/15 21:00:39 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef struct	s_flags
{
	int		space;
	int		plus;
	int		minus;
	int		hash;
	int		zero;
}						t_flags;

typedef struct	s_formatting
{
	t_flags	*flags;
	int		sign;
	int		width;
	int		precision;
	int		length_modifier;
}						t_formatting;

int		ft_printf(const char *format, ...);
int		find_end_spec(char chr);
t_flags	*check_flags(const char *format);
int		check_sign(const char *format);
int		check_width(const char *format);
int		check_precision(const char *format);
int		check_length_modifier(const char *format);
void	print_sequence(t_formatting *e_sequence);

/* hex.c */
char 	*hex_long_int(long int n);
int 	num_hex_len(long int n);

/* handler_p */
char	*handler_p(const char *format, va_list arg, t_formatting *e_sequence);
#endif
