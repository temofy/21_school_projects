/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:23:51 by cheller           #+#    #+#             */
/*   Updated: 2019/03/10 20:08:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef struct	s_formatting
{
	char	*flag;
	int		sign;
	int		width;
	int		precision;
	int		length_modifier;
}						t_formatting;

int		ft_printf(const char *format, ...);
int		find_end_spec(char chr);
char	*check_flag(const char *format);
int		check_sign(const char *format);
int		check_width(const char *format);
int		check_precision(const char *format);
int		check_length_modifier(const char *format);

#endif
