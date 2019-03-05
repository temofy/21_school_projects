/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/03/05 17:04:29 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char	*format_d(const char *format, char flag, va_list arg)
{
	int		d;
	char	*str;

	d = va_arg(arg, int);
	str = ft_itoa(d);
	return (str);
}
char	check_flag(const char *format)
{
	if (*format == '-')
		return (*format);
	else if (*format == '+')
		return (*format);
	else if (*format == '0')
		return (*format);
	else if (*format == ' ')
		return (*format);
	else if (*format == '#')
		return (*format);
	return ('\0');
}

char	*find_specifier(const char *format, va_list arg)
{
	char	*s;
	int		i;
	char	flag;

	i = 0;
	flag = check_flag(format);
	while (format[i++])
	{
		if (format[i] == 'd'	|| format[i] == 'i')
			return (format_d(format, flag, arg));
		else if (format[i]== 'f');
		else if (format[i] == 'c');
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

int		find_end_spec(char chr)
{
	if (chr == 'c')
		return (1);
	else if (chr == 'd')
		return (1);
	else if (chr == 'f')
		return (1);
	else if (chr == 'g')
		return (1);
	else if (chr == 'i')
		return (1);
	else if (chr == 's')
		return (1);
	else if (chr == '%')
		return (1);
	return (0);
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
	float	Pi = 3.14;

	ft_printf("- Hello, dude! My name is %s. I'm %d. How are you?\n%s\n", "Artem", 20, "- Nice, thanks!");
	printf("%s Меня зовут %-10s. Мне %10d лет.\n Число Пи = %.2f, Pointer: %15p\n", greeting, name, age, Pi, &greeting);
	//ft_putstr(s);
	return (1);
}