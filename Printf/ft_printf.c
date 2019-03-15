/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/03/15 20:07:26 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	print_sequence(t_formatting *e_sequence)
{
	printf("*************-escape-sequence-*************\n");
	printf("flags: \n\tflag_space: %d\n", e_sequence->flags->flag_space);
	printf("\tflag_plus: %d\n", e_sequence->flags->flag_plus);
	printf("\tflag_minus: %d\n", e_sequence->flags->flag_minus);
	printf("\tflag_hash: %d\n", e_sequence->flags->flag_hash);
	printf("\tflag_zero: %d\n", e_sequence->flags->flag_zero);
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

char	*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_seq)
{
	int		flags_amount;
	int		flag_minus;
	int		flag_plus;

	flag_minus = 0;
	flag_plus = 0;
	flags_amount = ft_strlen(e_seq->flag);
	while (flags_amount > 0)
	{
		if (*(e_seq->flag) == '0') // flag "0"
			ft_memset(*str, '0', len_str);
		else if (*(e_seq->flag) == '-') // flag "-"
		{
			ft_memset(*str, ' ', len_str);
			flag_minus = 1;
			//*str = ft_strjoin(*str_arg, *str);			
		}
		else if (*(e_seq->flag) == '+') // flag "+"
		{
			flag_plus = 1;
			if (len_str > 0)
			{
				if (**str_arg == '-')
					ft_memset(*str, ' ', len_str);
				else
				{
					ft_memset(*str, ' ', len_str - 1);
					*str_arg = ft_strjoin("+", *str_arg);
					//ft_memset(*str + len_str - 1, '+', 1);
				}
			}
			else
				if (**str_arg != '-')
					*str = ft_strfjoin(*str, "+");
		}
		else if (*(e_seq->flag) == ' ' && !flag_minus && !flag_minus) // flag " "
		{
				**str = ' ';
		}
		else
			ft_memset(*str, ' ', len_str);
		flags_amount--;
	}
	if (flag_minus)
		*str = ft_strjoin(*str_arg, *str);
	else		
		*str = ft_strjoin(*str, *str_arg); //утечка
	//return (flags_amount > 1) ? *str : handler_d_f-lags(&*str, &*str_arg, len_str, e_seq);
	return (*str);
}

/*char	*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_sequence)
{
	if (ft_strlen(e_sequence->flag) == 1)
	{
		if (*(e_sequence->flag) == '0') // flag "0"
			ft_memset(*str, '0', len_str);
		else if (*(e_sequence->flag) == '-') // flag "-"
		{
			ft_memset(*str, ' ', len_str);
			*str = ft_strjoin(*str_arg, *str);
			return (*str);
		}
		else if (*(e_sequence->flag) == '+') // flag "+"
		{	
			if (len_str > 0)
			{
				if (**str_arg == '-')
					ft_memset(*str, ' ', len_str);
				else
				{
					ft_memset(*str, ' ', len_str - 1);
					*str_arg = ft_strjoin("+", *str_arg);
					//ft_memset(*str + len_str - 1, '+', 1);
				}
			}
			else
				if (**str_arg != '-')
					*str = ft_strfjoin(*str, "+");
		}
		else if (*(e_sequence->flag) == ' ') // flag " "
		{

		}
		else
			ft_memset(*str, ' ', len_str);
		*str = ft_strjoin(*str, *str_arg); //утечка
	}
	else
	{
		if (ft_strcmp(e_sequence->flag, "")){}
	}
	

	return (*str);
}*/

char	*handler_sequence_d(char **str_arg, t_formatting *e_sequence, char **str)
{
	int		length_arg;
	int		length_str;
	int		width;
	int		precision;

	width = e_sequence->width;
	precision = e_sequence->precision;
	length_arg = ft_strlen(*str_arg);	//arguments's length with sign
	length_str = handler_length(length_arg, width, precision); //counting remaining length
	printf("length: %d\n", length_str);
	printf("nbr: %s\n", *str_arg);
	//print_sequence(e_sequence);
	*str = ft_strnew(length_str);
	ft_memset(*str, ' ', length_str);
	if (*(e_sequence->flag) != '\0')
		return(*str = handler_d_flags(&*str, &*str_arg, length_str, e_sequence));
	else if (length_str > 0 && precision >= width)
		ft_memset(*str, '0', length_str);
	else if (length_str > 0 && width > precision && precision > length_arg)
	{
		ft_memset(*str, ' ', length_str);
		ft_memset(*str + (width - precision), '0', precision - length_arg);
	}
	else if (length_str > 0)
		ft_memset(*str, ' ', length_str);
	*str = ft_strjoin(*str, *str_arg); //утечка
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
	e_sequence->flags = check_flags(format);
	//printf("flag: %s\n", e_sequence->flags);
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
	e_sequence = scanning_sequence(format + 1); // need to free
	//print_sequence(e_sequence);
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'i')
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
		else if (format[i] == 'p')
			return (handler_p(format, arg, e_sequence));
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

	ft_printf("- Hello, dude! My name is %s. I'm % 05d. How are you?\n%s\n", "Artem", 20, "- Nice, thanks!");
	printf("%s Меня зовут %-10s. Мне % 05d лет.\n Число (int)Пи = %.0f, Pointer: %15p\n", greeting, name, age, Pi, greeting);
	
	//ft_printf("Age's address: %0.10p\n", &age);
	//printf("Age's adress: %p\n", &age);
	//printf("di: %.15f\n", (double)(i - 1.2));
	//printf("%3$i %i %i %i %5$i ", 10, 6, 7, 5, 4, 3);
	return (1);
}