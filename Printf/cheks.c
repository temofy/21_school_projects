/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:52:04 by cheller           #+#    #+#             */
/*   Updated: 2019/06/28 15:08:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		check_spec(const char *string)
{
	while (*string)
	{
		if (*string == 'a')
			return (*string);
		else if (*string == 'c')
			return (*string);
		else if (*string == 'd')
			return (*string);
		else if (*string == 'f')
			return (*string);
		else if (*string == 'g')
			return (*string);
		else if (*string == 'i')
			return (*string);
		else if (*string == 's')
			return (*string);
		else if (*string == 'Z')
			return (*string);
		else if (*string == '%')
			return (*string);
		string++;
	}
	return ('\0');
}

t_flags		*check_flags(const char *format)
{
	t_flags *flags;
	int		end;
	int		i;

	i = -1;
	end = find_index_end_spec(format);
	initialize_flags(&flags);
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

int			check_precision(const char *format)
{
	int	i;
	int	end;
	int	prec;

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

int			check_width(const char *f)
{
	int	i;
	int	end;
	int width;
	int	finded_d;

	finded_d = 0;
	end = find_index_end_spec(f);
	i = end;
	width = 0;
	while (--i >= 0)
	{
		if (f[i] >= '0' && f[i] <= '9')
			finded_d = 1;
		if (f[i - 1] == '.')
			finded_d = 0;
		if (((f[i - 1] < '0' || f[i - 1] > '9') || (i - 1) == -1) && finded_d)
		{
			if ((width = read_width(f, i, width)) > 0)
				break ;
		}
	}
	if (!width)
		width = -1;
	return (width);
}

int			check_length_modifier(const char *format)
{
	int length_modifier;

	length_modifier = -1;
	format += find_index_end_spec(format);
	while (*(--format) != '%')
	{
		if (*format == 'h')
		{
			length_modifier += 104 + 1;
			length_modifier -= (*(format - 1) == 'h') ? 1 : 0;
		}
		if (*format == 'l')
		{
			if (*format == 'l')
				return (216);
			return (108);
		}
		if (*format == 'L')
			return (76);
		if (*format == 'j')
			return (106);
		if (*format == 'z')
			return (122);
	}
	return (length_modifier);
}
