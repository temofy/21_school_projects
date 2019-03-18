/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:26:54 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 21:07:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* handler format "p" */

char    *handler_sequence_p(char *hex, t_formatting *e_seq)
{
	char	*str;
	int		length_str;
	int		length_arg;

	hex = ft_strfjoin("0x", hex, 2);
	length_arg = ft_strlen(hex);
	length_str = handler_length(length_arg, e_seq->width, e_seq->precision);
	str = ft_strnew(length_str);
	memset(str, ' ', length_str);
	str = ft_strfjoin(str, hex, 0);
    return (str);
}

char	*handler_p(va_list arg, t_formatting *e_sequence)
{
	char *hex;
	
	hex = hex_long_int((long int)va_arg(arg, void *));
	hex = handler_sequence_p(hex, e_sequence);
	ft_printf("hex: %s\n", hex);
	return (hex);
}