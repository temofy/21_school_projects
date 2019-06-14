/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:52:04 by cheller           #+#    #+#             */
/*   Updated: 2019/04/29 12:39:20 by cheller          ###   ########.fr       */
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
			width = read_width(f, i, width);
			if (!width)
				width = -1;
			return (width);
		}
	}
	return (-1);
}

int			check_length_modifier(const char *format)
{
	int i;

	i = find_index_end_spec(format) + 1;
	while (--i)
	{
		if (format[i - 1] == 'h')
		{
			if (format[i - 2] == 'h')
				return (208);
			return (104);
		}
		if (format[i - 1] == 'l')
		{
			if (format[i - 2] == 'l')
				return (216);
			return (108);
		}
		if (format[i - 1] == 'L')
			return (76);
		if (format[i - 1] == 'j')
			return (106);
		if (format[i - 1] == 'z')
			return (122);
	}
	return (-1);
}
