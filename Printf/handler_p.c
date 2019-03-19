/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:26:54 by cheller           #+#    #+#             */
/*   Updated: 2019/03/19 16:21:19 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/* handler format "p" */

char	*handler_p_flags(char *str, char *str_arg, int len_str, t_formatting *e_seq)
{
	if (e_seq->flags->zero && e_seq->precision == -1) 		// flag "0"
		ft_memset(str, '0', len_str);
	return (str);
}

char    *handler_sequence_p(char *hex, t_formatting *e_seq)
{
	char	*str;
	int		length_str;
	int		length_arg;

	length_arg = ft_strlen(hex);
	if (e_seq->precision > (length_arg))
	{
		length_str = e_seq->precision - length_arg;
		str = ft_strnew(length_str);
		ft_memset(str, '0', length_str);
		hex = ft_strfjoin(str, hex, 0);
		length_arg = ft_strlen(hex);
	}
	if ((length_str = (handler_length(length_arg, e_seq->width, e_seq->precision) - 2)) < 0)
		length_str = 0;
	//printf("len: %d\n", length_str);
	str = ft_strnew(length_str);
	ft_memset(str, ' ', length_str);
	if (e_seq->flags->zero && e_seq->precision == -1) 		// flag "0"
	{
		ft_memset(str, '0', length_str);
		hex = ft_strfjoin(str, hex, 0);
	}
	/*if (e_seq->precision > (length_arg))
		ft_memset(str, '0', length_)*/
	//length_arg = ft_strlen(hex);
	//else if ((length_arg + 2) < e_seq->width)
	hex = ft_strfjoin("0x", hex, 2);
	str = ft_strfjoin(str, hex, 0);
    return (str);
}

char	*handler_p(va_list arg, t_formatting *e_sequence)
{
	char *hex;
	
	hex = hex_long_int((long int)va_arg(arg, void *));
	hex = handler_sequence_p(hex, e_sequence);
	ft_printf("hex start: %s\n", hex);
	return (hex);
}