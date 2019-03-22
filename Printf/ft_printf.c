/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/03/22 21:41:10 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

void	print_sequence(t_formatting *e_sequence)
{
	printf("*************-escape-sequence-*************\n");
	printf("flags: \n\tspace: %d\n", e_sequence->flags->space);
	printf("\tplus: %d\n", e_sequence->flags->plus);
	printf("\tminus: %d\n", e_sequence->flags->minus);
	printf("\thash: %d\n", e_sequence->flags->hash);
	printf("\tzero: %d\n", e_sequence->flags->zero);
	printf("width: %d\n", e_sequence->width);
	printf("precision: %d\n", e_sequence->precision);
	printf("negative: %d\n", e_sequence->is_negative);
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
	return (e_sequence);
}

char	*handler_f(va_list arg, t_formatting *e_sequence)
{
	return ("\0");
}

char	*find_specifier(const char *format, va_list arg)
{
	//char	*s;
	int		i;
	t_formatting *e_sequence;

	i = 0;
	e_sequence = scanning_sequence(format + 1); // need to free
	//print_sequence(e_sequence);
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'D' || format[i] == 'i' )
			return (handler_d(arg, e_sequence));
		else if (format[i]== 'f' || format[i]== 'F')
			return (handler_f(arg, e_sequence));
		else if (format[i] == 'c' || format[i] == 'C')
			return (handler_c(arg, e_sequence));
		else if (format[i] == 's')
			return (handler_s(arg, e_sequence));
		else if (format[i] == 'p')
			return (handler_p(arg, e_sequence));
		else if (format[i] == 'u' || format[i] == 'U')
		{
			
		}
		else if (format[i] == 'o' || format[i] == 'O')
		{
			
		}
		else if (format[i] == 'x')
		{
			
		}
		else if (format[i] == 'X')
		{
			
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
	char	*string; // prepared string for print
	int		i;		// counter
	int		start;	// var to find pos after foramtting
	int		found_spec; // flag

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
	string = ft_strjoin(string, ft_strsub(format, start, i - start)); // проверить
	ft_putstr(string);
	va_end(arg);
	return (1);
}

int		main()
{
	char	*greeting = "Добрый вечер!";
	char	*name = "Artem";
	short age = 20;
	double	Pi = 3.14;
	//double	i = 1.1;

	//ft_printf("Hel%");
	//ft_printf("Hello %5s`#!\nMy %came is %10.2s\n%p\n", "world", 'n', name, &name);
	/* ft_printf("I'm % .05 d лет\n", 20); // will right process
	printf("I'm % .05 d лет\n", 20);*/
	//printf("%\n", 5);
	/*ft_printf("%.15.5.3.2.23.3.4 500 100 d\n", 2000); // space include in width, but not int precision
	printf("%.15.5.3.2.23.3.4. 500 -15 .10d\n", 2000); */
	ft_printf("number: %015.10d\n", 10);
	printf("number: %O\n", age);
	//printf("%0.2.2.2.2.3.4.5.5.4.5.4.5.4.5454.54. 456 567 56 7 8 89 1 0D\n tgrwe%  \n",5 );
	//printf("lol%10.5l+d\n", 505);
	//printf("Hello %7s!\nMy %5came is %10.2s\n%025p\n", "world", 'n', name, &name);
	//ft_printf("- Hello, dude! My name is %s. I'm %+05ld. How are you?\n%s\n", "Artem", age, "- Nice, thanks!");
	//printf("%s Меня зовут %-10s. Мне %+05hd лет.\n Число (int)Пи = %.0f, Pointer: %15p\n", greeting, name, age, Pi, greeting);
	
	//ft_printf("Age's address: %0.10p\n", &age);
	//printf("Age's adress: %p\n", &age);
	//printf("di: %.15f\n", (double)(i - 1.2));
	//printf("%3$i %i %i %i %5$i ", 10, 6, 7, 5, 4, 3);
	return (1);
}