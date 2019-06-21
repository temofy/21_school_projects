/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:40:10 by cheller           #+#    #+#             */
/*   Updated: 2019/06/01 12:42:52 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			initialize_flags(t_flags **flags)
{
	*flags = (t_flags*)malloc(sizeof(t_flags));
	(*flags)->minus = 0;
	(*flags)->plus = 0;
	(*flags)->zero = 0;
	(*flags)->space = 0;
	(*flags)->hash = 0;
}

int				find_index_end_spec(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
		{
			if (s[i] != 'l' && s[i] != 'h' && s[i] != 'L'
				&& s[i] != 'z' && s[i] != 'j')
				return (i);
		}
		else if (s[i] == '%')
			return (i);
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] != '#' && s[i] != ' ' && s[i] != '.' && s[i] != '+'
			&& s[i] != '-' && s[i] != 'l' && s[i] != 'h' && s[i] != 'L'
			&& s[i] != 'z' && s[i] != 'j')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

t_long_value	calculate_lv(t_long_value *result, int i, int len)
{
	t_long_value	decade_in_exp;
	t_long_value	tmp;
	t_long_value	tmp_next;
	t_long_value	tmp_result;

	decade_in_exp = la_pow(conv_to_la(10), len - i - 1);
	tmp = (la_pow(conv_to_la(5), i + 1));
	tmp_next = karatsuba_mul(tmp, decade_in_exp);
	tmp_result = *result;
	*result = sum(*result, tmp_next);
	free(tmp.values);
	free(decade_in_exp.values);
	free(tmp_next.values);
	free(tmp_result.values);
	return (*result);
}

int				read_width(const char *format, int i, int width)
{
	while (format[i] >= '0' && format[i] <= '9')
	{
		width *= 10;
		width += (format[i] - '0');
		i++;
	}
	return (width);
}

char			*addition_zeros(char *nbr, int length)
{
	char	*zeros;

	if (!(zeros = ft_strnew(length)))
		return (NULL);
	ft_memset(zeros, 48, length);
	nbr = ft_strfjoin(nbr, zeros, 0);
	return (nbr);
}
