/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/03/10 20:29:55 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	print_sequence(t_formatting *e_sequence)
{
	printf("*************-escape-sequence-*************\n");
	printf("flag: %s\n", e_sequence->flag);
	printf("width: %d\n", e_sequence->width);
	printf("precision: %d\n", e_sequence->precision);
	printf("sign: %d\n", e_sequence->sign);
	printf("length_modifier: %d\n", e_sequence->length_modifier);
	printf("********************************************\n");
}

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

char	*handler_d_flags(char **str, char **str_d, int length_str, t_formatting *e_sequence)
{
	if (ft_strlen(e_sequence->flag) == 1)
	{
		if (ft_strncmp(e_sequence->flag, "0", 1) == 0)
			ft_memset(*str, '0', length_str);
		else if (ft_strncmp(e_sequence->flag, "-", 1) == 0)
		{
			ft_memset(*str, ' ', length_str);
			*str = ft_strjoin(*str_d, *str);
			return (*str);
		}
		else if (ft_strncmp(e_sequence->flag, "+", 1) == 0)
		{	
			if (length_str > 0)
			{
				if (**str_d == '-')
					ft_memset(*str, ' ', length_str);
				else
				{
					printf("Done\n");
					ft_memset(*str, ' ', length_str - 1);
					ft_memset(*str + length_str - 1, '+', 1);
				}
			}
			else
				if (**str_d != '-')
					*str = ft_strfjoin(*str, "+");
		}
		else
			ft_memset(*str, ' ', length_str);
		*str = ft_strjoin(*str, *str_d); //утечка
	}
	else
	{
		if (ft_strcmp(e_sequence->flag, "")){}
	}
	

	return (*str);
}

char	*handler_sequence_d(char **str_d, t_formatting *e_sequence, char **str)
{
	int		length_d;
	int		length_str;
	int		width;
	int		precision;

	width = e_sequence->width;
	precision = e_sequence->precision;
	length_d = ft_strlen(*str_d);
	length_str = handler_length(length_d, width, precision);
	printf("length: %d\n", length_str);
	printf("nbr: %s\n", *str_d);
	//print_sequence(e_sequence);
	*str = ft_strnew(length_str);
	if (*(e_sequence->flag) != '\0')
		return(*str = handler_d_flags(&*str, &*str_d, length_str, e_sequence));
	else if (length_str > 0 && precision >= width)
		ft_memset(*str, '0', length_str);
	else if (length_str > 0 && width > precision && precision > length_d)
	{
		ft_memset(*str, ' ', length_str);
		ft_memset(*str + (width - precision), '0', precision - length_d);
	}
	else if (length_str > 0)
		ft_memset(*str, ' ', length_str);
	*str = ft_strjoin(*str, *str_d); //утечка
	return (*str);
}

char	*handler_d(const char *format, va_list arg, t_formatting *e_sequence)
{
	char	*nbr_str;
	char	*str;	
	int		length;

	nbr_str = ft_itoa(va_arg(arg, int)); // для разных флагов
	str = handler_sequence_d(&nbr_str, e_sequence, &str);
	return (str);
}

char	*handler_f(const char *format, va_list arg, t_formatting *e_sequence)
{
	return ("\0");
}

char	*handler_c(const char *format, va_list arg, t_formatting *e_sequence)
{
	return ("\0");
}

t_formatting	*scanning_sequence(const char *format)
{
	t_formatting	*e_sequence;

	if (!(e_sequence = (t_formatting*)malloc(sizeof(t_formatting))))
		return (NULL);
	e_sequence->flag = check_flag(format);
	//printf("flag: %s\n", e_sequence->flag);
	e_sequence->width = check_width(format);
	e_sequence->precision = check_precision(format);
	e_sequence->sign = check_sign(format);
	e_sequence->length_modifier = check_length_modifier(format);
	return (e_sequence);
}

char	*find_specifier(const char *format, va_list arg)
{
	char	*s;
	int		i;
	t_formatting *e_sequence;

	i = 0;
	e_sequence = scanning_sequence(format + 1);
	//print_sequence(e_sequence);
	while (format[i++])
	{
		if (format[i] == 'd'	|| format[i] == 'i')
			return (handler_d(format, arg, e_sequence));
		else if (format[i]== 'f')
			return (handler_f(format, arg, e_sequence));
		else if (format[i] == 'c')
			return (handler_c(format, arg, e_sequence));
		else if (format[i] == 's')
		{
			s = va_arg(arg, char*);
			return (s);
		}
		else if (format[i] == '%')
		{
			
		}
	}
	return (NULL);
}

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*string;
	int		i;
	int		start;
	int		found_spec;

	i = 0;
	string = ft_strnew(0);
	start = 0;
	found_spec = 0;
	va_start(arg, format);
	// нужна проверку на количество спецификаций с количеством аргументом
	while (format[i])
	{
		if (format[i] == '%' && !found_spec)
		{
			found_spec = 1;
			string = ft_strjoin(string, ft_strsub(format, start, i - start));
			string = ft_strjoin(string, find_specifier(format + i, arg));
		}
		else if (found_spec)
		{
			if (find_end_spec(format[i]))
			{
				start = i + 1;
				found_spec = 0;			
			}
		}
		i++;
	}
	string = ft_strjoin(string, ft_strsub(format, start, i - start));
	ft_putstr(string);
	va_end(arg);
	return (1);
}

int		main()
{
	char	*greeting = "Добрый вечер!";
	char	*name = "Artem";
	int		age = 20;
	double	Pi = 3.14;
	//double	i = 1.1;

	ft_printf("- Hello, dude! My name is %s. I'm %+-6d. How are you?\n%s\n", "Artem", -20, "- Nice, thanks!");
	printf("%s Меня зовут %-10s. Мне %-+6d лет.\n Число (int)Пи = %.0f, Pointer: %15p\n", greeting, name, age, Pi, greeting);
	//printf("di: %.15f\n", (double)(i - 1.2));
	return (1);
}