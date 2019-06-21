/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:34:32 by cheller           #+#    #+#             */
/*   Updated: 2019/06/14 13:34:35 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*find_spec_add(const char *f, va_list arg, t_formatting *e_seq, int i)
{
	if (f[i] == 's')
		return (handler_s(arg, e_seq));
	else if (f[i] == 'S')
		return (handler_str_unicode(arg, e_seq));
	else if (f[i] == 'p')
		return (handler_p(arg, e_seq));
	else if (f[i] == 'u')
		return (handler_u(arg, e_seq));
	else if (f[i] == 'U')
		return (handler_big_u(arg, e_seq));
	else if (f[i] == 'o')
		return (handler_o(arg, e_seq));
	else if (f[i] == 'x')
		return (handler_x(arg, e_seq));
	else if (f[i] == 'X')
		return (handler_x_big(arg, e_seq));
	else if (f[i] == 'Z')
		return (undefined_behavior(arg, e_seq));
	else if (f[i] == '%')
		return (handler_percent(e_seq));
	return (NULL);
}

char	*find_specifier(const char *format, va_list arg, t_formatting *e_seq)
{
	int		i;
	char	*str;

	i = 0;
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'i')
			return (handler_d(arg, e_seq));
		else if (format[i] == 'f' || format[i] == 'F')
			return (handler_f(arg, e_seq));
		else if (format[i] == 'b')
			return (handler_b(arg, e_seq));
		else if (format[i] == 'c')
			return (handler_c(arg, e_seq));
		else if (format[i] == 'C')
			return (handler_chr_unicode(arg, e_seq));
		else
		{
			str = find_spec_add(format, arg, e_seq, i);
			if (str != NULL)
				return (str);
		}
	}
	return (ft_strnew(0));
}
