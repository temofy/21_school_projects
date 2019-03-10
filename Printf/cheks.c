/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 12:52:04 by cheller           #+#    #+#             */
/*   Updated: 2019/03/10 20:08:27 by cheller          ###   ########.fr       */
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


char	*check_flag(const char *format)
{
	char 	*flag;

	flag = ft_strnew(0);
	while (format)
	{
		if (*format == '-')
			flag = ft_strfjoin(flag, "-");
		else if (*format == '+')
			flag = ft_strfjoin(flag, "+");
		else if (*format == '0')
			flag = ft_strfjoin(flag, "0");
		else if (*format == ' ')
			flag = ft_strfjoin(flag, " ");
		else if (*format == '#')
			flag = ft_strfjoin(flag, "#");
		else
			break;
		format++;
	} 
	return (flag);
}

/*char	check_flag(const char *format)
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
}*/

int		check_sign(const char *format)
{
	if (*format == '-')
		return (1);
	return (0);
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
			if (!(find_end_spec(i + 1)) && format[i + 1] == 'l')
				return (216);
			return (108);
		}
		if (format[i] == 'L')
			return (76);
	}
	return (-1);
}