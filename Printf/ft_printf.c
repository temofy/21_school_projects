/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/02/27 13:32:32 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		format_d(const char *format, va_list arg)
{
	int		d;

	d = va_arg(arg, int);
	ft_putnbr(d);
	//format ++;
	return (1);
}

int		find_specifier(const char *format, va_list arg)
{
	char	*s;

	if (*format == '%')
	{
		if (*(format + 1) == 'd'	|| *(format + 1) == 'i')
		{
			format_d(format, arg);
			return (1);
		}
		else if (*(format + 1) == 'f');
		else if (*(format + 1) == 'c');
		else if (*(format + 1) == 's')
		{
			s = va_arg(arg, char*);
			ft_putstr(s);
			return (1);
		}
		else if (*(format + 1) == '%')
		{

		}
		format++;
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	int		done;
	char	*string;

	va_start(arg, format);
	// нужна проверку на количество спецификаций с количеством аргументом
	while (*format)
	{
		if (find_specifier(format, arg))
			format += 1;
		else
			ft_putchar(*format);
		format++;
	}
	va_end(arg);
	return (done);
}

int		main()
{
	char	*greeting = "Добрый вечер!";
	char	*name = "Artem";
	int		age = 20;

	ft_printf("Hello %d world! My name is %s\n", 60, "Artem");
	printf("%s Меня зовут %s. Мне %.1d лет.\n", greeting, name, age);
	//ft_putstr(s);
	return (1);
}
/* FLOAT!!!!!!!!FLOAT!!!!!!!!FLOAT#
int int_c(float x)
{
  while(x != (float)(int)x)
    x *= 10;
  return ((int)x);
}

int main() {
float a = -1.99999;
int b = (float)(int)a;
ft_putnbr(b);
write(1, ".", 1);
float c = a > 0? a - b : b - a;
int n = int_c(c);
ft_putnbr(n);
  return 0;
}
END OF FLOAT
*/