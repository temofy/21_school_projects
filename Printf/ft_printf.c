/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/05/28 16:38:23 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <math.h>

int		handler_length(int length, int width, int precision)
{
	if (length > width && length > precision)
		return (0);
	else if (length < width && length >= precision)
		return (width - length);
	else if (length >= width && length < precision)
		return (precision - length);
	else if (length < width && length < precision)
	{
		if (width > precision)
			return (width - length);
		else
			return (precision - length);
	}
	return (0);
}

int		count_amount_flags(t_formatting *e_seq)
{
	int		amount;

	amount = 0;
	amount += e_seq->flags->space;
	amount += e_seq->flags->plus;
	amount += e_seq->flags->minus;
	amount += e_seq->flags->hash;
	amount += e_seq->flags->zero;
	return (amount);
}

t_formatting	*scanning_sequence(const char *format)
{
	t_formatting	*e_sequence;

	if (!(e_sequence = (t_formatting*)malloc(sizeof(t_formatting))))
		return (NULL);
	e_sequence->flags = check_flags(format);
	e_sequence->width = check_width(format);
	e_sequence->precision = check_precision(format);
	e_sequence->length_modifier = check_length_modifier(format);
	e_sequence->specifier = check_spec(format);
	e_sequence->common_length = 0; // везде записывать
	return (e_sequence);
}

char	*handler_percent(t_formatting *e_seq)
{
	char	*str;
	int		str_len;

	str_len = handler_length(1, e_seq->width, 0);
	str = ft_strnew(str_len);
	ft_memset(str, ' ', str_len);
	e_seq->common_length += str_len + 1;
	if (e_seq->flags->minus)
		str = ft_strfjoin("%", str, 2);
	else
		str = ft_strfjoin(str, "%", 1);
	return (str);
}

char	*find_specifier(const char *format, va_list arg, t_formatting *e_sequence)
{
	int		i;

	i = 0;
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'i' )
			return (handler_d(arg, e_sequence));
		else if (format[i]== 'f' || format[i]== 'F')
			return (handler_f(arg, e_sequence));
        else if (format[i]== 'b' || format[i]== 'B')
            return (handler_b(arg, e_sequence));
		else if (format[i] == 'c' || format[i] == 'C')
			return (handler_c(arg, e_sequence));
		else if (format[i] == 's')
			return (handler_s(arg, e_sequence));
		else if (format[i] == 'p')
			return (handler_p(arg, e_sequence));
		else if (format[i] == 'u' || format[i] == 'U')
			return (handler_u(arg, e_sequence));
		else if (format[i] == 'o' || format[i] == 'O')
			return(handler_o(arg, e_sequence));
		else if (format[i] == 'x')
			return(handler_x(arg, e_sequence));
		else if (format[i] == 'X')
			return(handler_x_big(arg, e_sequence));
		else if (format[i] == '%')
			return (handler_percent(e_sequence));
	}
	return (NULL);
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
	i = -1;
	string = ft_strnew(0);
	start = 0;
	found_spec = 0;
	va_start(arg, format);
	// нужна проверку на количество спецификаций с количеством аргументом
	while (format[++i])
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
		}
		else if (found_spec)
		{
			if (find_end_spec(format[i]))
			{
				start = i + 1;
				found_spec = 0;
			}
		}
		else
			common_length++;
	}
	string = ft_strljoin(string, ft_strsub(format, start, i - start), common_length - (i - start), (i - start)); // проверить
	write(1, string, common_length);
	va_end(arg);
	return (common_length);
}

int		main()
{
	ft_printf("%d %d %d\n", 1, -2, 33);
	printf("%d %d %d\n", 1, -2, 33);
	ft_printf("%d %d %d %d\n", 1, -2, 33, 42);
	printf("%d %d %d %d", 1, -2, 33, 42);
	/*ft_printf("number: %jd\n", 32769);
	printf("number: %jd\n", 32769);*/

	//ft_printf("%-#10.5o\n", -16);
	//printf("%-10.0o", 0);
	//ft_printf("%3$i %i %i %i %5$i \n", 10, 6, 7, 5, 4, 3);
	//printf("%3$i %i %i %i %5$i ", 10, 6, 7, 5, 4, 3);
	//printf("%e\n", 6553.12412);
	return (0);
}
