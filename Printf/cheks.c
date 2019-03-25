/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:52:04 by cheller           #+#    #+#             */
/*   Updated: 2019/03/25 18:24:03 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*int		find_end_spec(char chr)
{
	if (chr == 'a')
		return (1);
	else if (chr == 'c')
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
}*/

int		find_end_spec(const char chr)
{
	if ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z'))
	{
		if (chr != 'l' && chr != 'h' && chr != 'L') // continue
			return (1);
	}
	else if (chr == '%')
		return (1);
	return (0);
}
int		find_index_end_spec(const char *string)
{
	int		i;

	i = 0;
	while(string[i])
	{
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z'))
		{
			if (string[i] != 'l' && string[i] != 'h' && string[i] != 'L') // continue
				return (i);
		}
		else if (string[i] == '%')
			return (i);
		i++;
	}
	return (i);
}

t_flags	*check_flags(const char *format)
{
	t_flags *flags;
	int		end;
	int		i;

	i = -1;
	end = find_index_end_spec(format);
	flags = (t_flags*)malloc(sizeof(t_flags));
	flags->minus = 0;
	flags->plus = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->hash = 0;
	while (format[++i] && i < end)
	{
		if (format[i] == '-')
			flags->minus = 1;
		else if (format[i] == '+')
			flags->plus = 1;
		else if (format[i] == '0')
		{
			if (format[i - 1] > '9' || format[i - 1] < '0')
				flags->zero = 1;
		}
		else if (format[i] == ' ')
			flags->space = 1;
		else if (format[i] == '#')
			flags->hash = 1;
	} 
	return (flags);
}

int		check_precision(const char *format)
{
	int		i;
	int		end;
	int 	prec;

	end = find_index_end_spec(format);
	i = end;
	prec = 0;
	while (format[--i] != '%')
	{
		if ((format[i] == '.'))
		{
			while (format[++i] >= '0' && format[i] <= '9')
			{
				prec *= 10;
				prec += (format[i] - '0');
			}
			return (prec);
		}
	}
	return (-1);
}

/*int		check_precision(const char *format)
{
	int		i;
	int		length;
	int		start;
	char	*prec_str;
	int		end;

	end = find_index_end_spec(format);
	i = -1;
	length = 0;
	while (format[++i] != '.' && i < end);
	if ((format[i] == '.') && (i + 1 == end))
		return(0);
	if (i == end)
		return (-1);
	start = i + 1;
	while(format[++i] >= '0' && format[i] <= '9')
		length++;
	prec_str = ft_strnew(length);
	prec_str = ft_strncpy(prec_str, format + start, length);
	return(ft_atoi(prec_str));
}*/

/*int		check_width(const char *format)
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
}*/

int		check_width(const char *format)
{
	int		i;
	int		end;
	int 	width;
	int		finded_digit;

	finded_digit = 0;
	end = find_index_end_spec(format);
	i = end;
	width = 0;
	while (--i >= 0)
	{
		if (format[i] >= '0' && format[i] <= '9')
			finded_digit = 1;
		if (format[i - 1] == '.')
			finded_digit = 0;
		if (((format[i - 1] < '0' || format[i - 1] > '9') || (i - 1) == -1) && finded_digit) 
		{
			while (format[i] >= '0' && format[i] <= '9')
			{
				width *= 10;
				width += (format[i] - '0');
				i++;
			}
			if (!width)
				width = -1;
			return (width);
		}
	}
	return (-1);
}

int	check_length_modifier(const char *format)
{
	int 	i;

	i = find_index_end_spec(format);
	if (i != 0)
	{
	/*while (!(find_end_spec(format[++i])))
	{*/
		if (format[i - 1] == 'h')
		{
			/*if (!(find_end_spec(i + 1)) && format[i + 1] == 'h')
				return (208);*/
			return (104);
		}
		if (format[i - 1] == 'l')
		{
			/*if (!(find_end_spec(i + 1)) && format[i + 1] == 'l')
				return (216);*/
			return (108);
		}
		if (format[i - 1] == 'L')
			return (76);
	}
	return (-1);
}