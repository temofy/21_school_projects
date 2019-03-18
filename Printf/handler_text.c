/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:51:30 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 20:56:06 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_sequence_s(char *str_arg, char **str, t_formatting *e_sequence)
{
	int		length_arg;
	int		length_str;
	char	*tmp;

	length_arg = ft_strlen(str_arg);	//arguments's length with sign
	if (e_sequence->precision != -1 && e_sequence->precision < length_arg)
	{
		length_arg = e_sequence->precision;
		tmp = str_arg; // поглядеть
		str_arg = ft_strsub(str_arg, 0, length_arg);
		//free(tmp);
	}	
	length_str = handler_length(length_arg, e_sequence->width, 0);
	*str = ft_strnew(length_str);
	ft_memset(*str, ' ', length_str); 
	if (!e_sequence->flags->minus)
		*str = ft_strfjoin(*str, str_arg, 3); 
	else
		*str = ft_strfjoin(str_arg, *str, 3);
	return (*str);
}
char	*handler_s(va_list arg, t_formatting *e_sequence) // учесть '\0'
{
	char	*str;	
	char	*str_arg;

	str_arg = va_arg(arg, char*);
	str = handler_sequence_s(str_arg, &str, e_sequence);
	return (str);
}

char	*handler_c(va_list arg, t_formatting *e_sequence) // учесть '\0'
{
	char	*str;
	char	chr;
	int		length_str;

	chr = va_arg(arg, int);
	length_str = handler_length(1, e_sequence->width, 0);
	str = ft_strnew(length_str + 1);
	ft_memset(str, ' ', length_str + 1);
	if (!e_sequence->flags->minus)
		*(str + length_str) = chr; 
	else
		*str = chr;
	return (str);
}