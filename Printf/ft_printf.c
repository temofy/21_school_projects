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
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

t_formatting	*scanning_sequence(const char *format)
{
	t_formatting	*e_sequence;

	if (!(e_sequence = (t_formatting*)malloc(sizeof(t_formatting))))
		return (NULL);
	e_sequence->flags = check_flags(format);
	e_sequence->width = check_width(format);
	e_sequence->is_negative = 0;
	e_sequence->precision = check_precision(format);
	e_sequence->length_modifier = check_length_modifier(format);
	e_sequence->specifier = check_spec(format);
	e_sequence->common_length = 0;
	return (e_sequence);
}

char 	*find_spec_add(const char *format, va_list arg, t_formatting *e_seq, int i)
{
	if (format[i] == 's')
		return (handler_s(arg, e_seq));
	else if (format[i] == 'S')
		return (handler_str_unicode(arg, e_seq));
	else if (format[i] == 'p')
		return (handler_p(arg, e_seq));
	else if (format[i] == 'u')
		return (handler_u(arg, e_seq));
	else if (format[i] == 'o')
		return(handler_o(arg, e_seq));
	else if (format[i] == 'x')
		return(handler_x(arg, e_seq));
	else if (format[i] == 'X')
		return(handler_x_big(arg, e_seq));
	else if (format[i] == 'Z')
		return(undefined_behavior(arg, e_seq));
	else if (format[i] == '%')
		return (handler_percent(e_seq));
	return (NULL);
}

char	*find_specifier(const char *format, va_list arg, t_formatting *e_seq)
{
	int		i;
	char 	*str;

	i = 0;
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'i' )
			return (handler_d(arg, e_seq));
		else if (format[i]== 'f')
			return (handler_f(arg, e_seq));
        else if (format[i]== 'b')
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

void	found_spec(char *format, char *str, va_list arg)
{
	char			*substr;
	t_formatting	*e_seq;

}

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*string;
	char	*substr;
	int		i;
	int		start;
	int		found_spec;
	t_formatting *e_sequence;
	size_t	common_length;

	common_length = 0;
	i = 0;
	string = ft_strnew(0);
	start = 0;
	found_spec = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%' && !found_spec)
		{
			e_sequence = scanning_sequence(format + i + 1);
			found_spec = 1;
			if (start == 0)
				string = ft_strljoin(string, ft_strsub(format, start, i - start), 0, i - start);
			else
				string = ft_strljoin(string, ft_strsub(format, start, i - start), common_length - (i - start), i - start);
			substr = find_specifier(format + i, arg, e_sequence);
			string = ft_strljoin(string, substr, common_length, e_sequence->common_length);
			common_length += e_sequence->common_length;
			free(e_sequence->flags);
			free(e_sequence);
			i++;
		}
		else if (found_spec)
		{
			int end_spec_i = find_index_end_spec(format + i);
			start = end_spec_i + i + 1;
			found_spec = 0;
			i += end_spec_i + 1;
		}
		else
			{
			common_length++;
			i++;
		}
	}
	string = ft_strljoin(string, ft_strsub(format, start, i - start), common_length - (i - start), (i - start));
	write(1, string, common_length);
	free(string);
	va_end(arg);
	return (common_length);
}

int 	main()
{
	ft_printf("a%Sc%S\n", L"A", L"H");
	ft_printf("a%Sc%S\n", L"我", L"猫");
	ft_printf("%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S%S\n",
	L"Α α", L"Β β", L"Γ γ", L"Δ δ", L"Ε ε", L"Ζ ζ", L"Η η", L"Θ θ", L"Ι ι", L"Κ κ", L"Λ λ", L"Μ μ",
	L"Ν ν", L"Ξ ξ", L"Ο ο", L"Π π", L"Ρ ρ", L"Σ σ", L"Τ τ", L"Υ υ", L"Φ φ", L"Χ χ", L"Ψ ψ", L"Ω ω", L"");
	ft_printf("a%S", L"\x50\n");
	ft_printf("a%S\n", L"\xF0\x90\x8D\x86");
	printf("a%S\n", L"\xF0\x90\x8D\x86");
	ft_printf("% h");
	//ft_printf("%x\n", -42);
	//printf("%x", -42);
}