/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:52:04 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 21:18:44 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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


t_flags	*check_flags(const char *format)
{
	t_flags *flags;

	flags = (t_flags*)malloc(sizeof(t_flags));
	flags->minus = 0;
	flags->plus = 0;
	flags->zero = 0;
	flags->space = 0;;
	flags->hash = 0;
	while (format)
	{
		if (*format == '-')
			flags->minus = 1;
		else if (*format == '+')
			flags->plus = 1;
		else if (*format == '0')
			flags->zero = 1;
		else if (*format == ' ')
			flags->space = 1;
		else if (*format == '#')
			flags->hash = 1;
		else
			break;
		format++;
	} 
	return (flags);
}

int		check_precision(const char *format)
{
	int		i;
	int		length;
	int		start;
	char	*prec_str;

	i = -1;
	length = 0;
	while (format[++i] != '.' && !find_end_spec(format[i]));
	if ((format[i] == '.') && find_end_spec(format[i + 1]))
		return(0);
	if (find_end_spec(format[i]))
		return (-1);
	start = i + 1;
	while(format[++i] >= '0' && format[i] <= '9')
		length++;
	prec_str = ft_strnew(length);
	prec_str = ft_strncpy(prec_str, format + start, length);
	return(ft_atoi(prec_str));
}

int		check_width(const char *format)
{
	int		i;
	int		length;
	char	*width_str;
	int		start;

	length = 0;
	i = -1;
	while ((format[++i] < '0' || format[i] > '9') && format[i] != '.' && !find_end_spec(format[i]));
	if ((format[i] == '.'))
		return(-1);
	if (find_end_spec(format[i]))
		return (-1);
	start = i;
	while(format[i] >= '0' && format[i++] <= '9')
		length++;
	width_str = ft_strnew(length);
	width_str = ft_strncpy(width_str, format + start, length);
	return (ft_atoi(width_str));
}

int	check_length_modifier(const char *format)
{
	int 	i;

	i = -1;
	while (!(find_end_spec(format[++i])))
	{
		if (format[i] == 'h')
		{
			if (!(find_end_spec(i + 1)) && format[i + 1] == 'h')
				return (208);
			return (104);
		}
		if (format[i] == 'l')
		{
			/*if (!(find_end_spec(i + 1)) && format[i + 1] == 'l')
				return (216);*/
			return (108);
		}
		if (format[i] == 'L')
			return (76);
	}
	return (-1);
}