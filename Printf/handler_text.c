/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:51:30 by cheller           #+#    #+#             */
/*   Updated: 2019/04/12 14:14:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_sequence_s(char *str_arg, char **str, t_formatting *e_seq)
{
	int		length_arg;
	int		length_str;
	char	*tmp;

	length_arg = ft_strlen(str_arg);
	if (e_seq->precision != -1 && e_seq->precision < length_arg)
	{
		length_arg = e_seq->precision;
		tmp = str_arg;
		str_arg = ft_strsub(str_arg, 0, length_arg);
		free(tmp);
	}
	length_str = handler_length(length_arg, e_seq->width, 0);
	e_seq->common_length = length_str + length_arg;
	*str = ft_strnew(length_str);
	if (e_seq->flags->zero && !e_seq->flags->minus)
		ft_memset(*str, '0', length_str);
	else
		ft_memset(*str, ' ', length_str);
	if (!e_seq->flags->minus)
		*str = ft_strfjoin(*str, str_arg, 0);
	else
		*str = ft_strfjoin(str_arg, *str, 0);
	return (*str);
}

char	*handler_s(va_list arg, t_formatting *e_seq)
{
	char	*str;
	char	*str_arg;
	int		len_arg;

	str_arg = va_arg(arg, char *);
	if (str_arg == NULL)
		str_arg = ft_strdup("(null)");
	else
	{
		len_arg = ft_strlen(str_arg);
		str_arg = ft_strcpy(ft_strnew(len_arg), str_arg);
	}
	str = handler_sequence_s(str_arg, &str, e_seq);
	return (str);
}

char	*handler_c(va_list arg, t_formatting *e_seq)
{
	char	*str;
	char	chr;
	int		length_str;

	chr = va_arg(arg, int);
	length_str = handler_length(1, e_seq->width, 0);
	str = ft_strnew(length_str + 1);
	e_seq->common_length = length_str + 1;
	if (e_seq->flags->zero && !e_seq->flags->minus)
		ft_memset(str, '0', length_str + 1);
	else
		ft_memset(str, ' ', length_str + 1);
	if (!e_seq->flags->minus)
	{
		*(str + length_str) = chr;
	}
	else
		*str = chr;
	return (str);
}
