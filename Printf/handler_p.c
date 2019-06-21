/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:26:54 by cheller           #+#    #+#             */
/*   Updated: 2019/06/20 15:00:00 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pointer(char **str, char *hex, t_formatting *e_seq)
{
	if (!e_seq->flags->zero)
		hex = ft_strfjoin("0x", hex, 2);
	if (e_seq->flags->minus)
		*str = ft_strfjoin(hex, *str, 0);
	else
		*str = ft_strfjoin(*str, hex, 0);
	if (e_seq->flags->zero)
		*str = ft_strfjoin("0x", *str, 2);
	return (*str);
}

char	*in_if(char **str)
{
	*str = ft_strnew(2);
	*str = ft_strcpy(*str, "0x");
	return (*str);
}

char	*handler_sequence_p(char **str, char *hex, t_formatting *e_seq)
{
	int		len_str;
	int		len_arg;
	int		len_zeros;

	len_zeros = 0;
	len_str = 0;
	len_arg = ft_strlen(hex);
	if ((e_seq->precision == 0 || e_seq->width == 0) && ft_strequ(hex, "0"))
		return (in_if(str));
	if (e_seq->precision > len_arg)
		len_zeros = e_seq->precision - len_arg;
	hex = ft_strfjoin(ft_strnew_set(48, len_zeros), hex, 0);
	len_arg += len_zeros;
	if (e_seq->width - 2 > len_arg)
		len_str = e_seq->width - len_arg - 2;
	*str = ft_strnew(len_str);
	if (e_seq->precision > -1 || e_seq->flags->minus)
		e_seq->flags->zero = 0;
	if (e_seq->flags->zero && !e_seq->flags->minus)
		*str = ft_memset(*str, 48, len_str);
	else
		*str = ft_memset(*str, ' ', len_str);
	*str = pointer(str, hex, e_seq);
	return (*str);
}

char	*handler_p(va_list arg, t_formatting *e_sequence)
{
	char	*hex;
	char	*str;

	hex = hex_long_int(va_arg(arg, long int));
	str = handler_sequence_p(&str,\
	hex_long_int((long int)va_arg(arg, void *)), e_sequence);
	ft_strdel(&hex);
	e_sequence->common_length = ft_strlen(str);
	return (str);
}
