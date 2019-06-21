/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/13 11:07:03 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	is_found_spec(const char *format, int *i, int *start, int *found_spec)
{
	int end_spec_i;

	end_spec_i = find_index_end_spec(format + *i);
	*start = end_spec_i + *i + 1;
	*found_spec = 0;
	*i += end_spec_i + 1;
	(*i)--;
}

void	concatenate_str(const char *f, char **str, va_list *arg, size_t *c_len)
{
	t_formatting	*e_seq;
	char			*substr;

	e_seq = scanning_sequence(f + 1);
	substr = find_specifier(f, *arg, e_seq);
	*str = ft_strljoin(*str, substr, *c_len, e_seq->common_length);
	*c_len += e_seq->common_length;
	free_e_sequence(&e_seq);
}

void	reading_format(const char *f, char **str, size_t *len, va_list *arg)
{
	int		i;
	int		found_spec;
	int		s;
	char	*sub;

	s = 0;
	found_spec = 0;
	i = -1;
	while (f[++i])
	{
		if (f[i] == '%' && !found_spec++)
		{
			sub = ft_strsub(f, s, i - s);
			*str = (s == 0) ? ft_strljoin(*str, sub, 0, i - s) :
					ft_strljoin(*str, sub, *len - (i - s), i - s);
			concatenate_str(f + i, &*str, &*arg, &*len);
		}
		else if (found_spec)
			is_found_spec(f, &i, &s, &found_spec);
		else
			(*len)++;
	}
	if (found_spec)
		i--;
	*str = ft_strljoin(*str, ft_strsub(f, s, i - s), *len - (i - s), (i - s));
}

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*string;
	size_t	common_length;

	common_length = 0;
	string = ft_strnew(0);
	va_start(arg, format);
	reading_format(format, &string, &common_length, &arg);
	write(1, string, common_length);
	free(string);
	va_end(arg);
	return (common_length);
}
