/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_unicode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 13:55:51 by cheller           #+#    #+#             */
/*   Updated: 2019/06/13 13:55:52 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_first_byte(char *wchar, t_unicode *unicode, int byte)
{
	char	*bin;
	char	*carry;

	bin = present_int_as_bin(unicode->b[0]);
	carry = ft_strsub(bin, 0, 2);
	bin = ft_strncpy(bin, "10", 2);
	wchar[byte] = bin_as_dec(bin);
	ft_strdel(&bin);
	return (carry);
}

void	handler_sec_byte(char *wchar, t_unicode *uni, int byte, char *carry)
{
	char	*bin;

	bin = present_int_as_bin(uni->b[1]);
	bin = ft_strncpy(bin + 6, carry, 2);
	bin = bin - 6;
	if (byte == 0)
		bin = ft_strncpy(bin, "110", 3);
	else
		bin = ft_strncpy(bin, "10", 2);
	wchar[byte] = bin_as_dec(bin);
	ft_strdel(&bin);
	ft_strdel(&carry);
}

void	handler_third_byte(char *wchar, t_unicode *uni, int byte, char *carry)
{
	char	*bin;

	bin = present_int_as_bin(uni->b[2]);
	bin = ft_strncpy(bin + 4, carry, 4);
	bin = bin - 4;
	if (byte == 0)
		bin = ft_strncpy(bin, "1110", 4);
	else
		bin = ft_strncpy(bin, "11110", 5);
	wchar[byte] = bin_as_dec(bin);
	ft_strdel(&bin);
	ft_strdel(&carry);
}

void	handler_fourth_byte(char *wchar, t_unicode *uni, int byte)
{
	char	*bin;
	char	*carry;

	bin = present_int_as_bin(uni->b[2]);
	carry = ft_strsub(bin, 3, 3);
	bin = ft_strncpy(bin + 5, carry, 3);
	bin = bin - 5;
	bin = ft_strncpy(bin, "11110", 5);
	wchar[byte] = bin_as_dec(bin);
	ft_strdel(&bin);
	ft_strdel(&carry);
}

char	*encode_bytes(t_unicode *unicode, int bytes)
{
	char	*wchar;
	char	*bin;
	char	*carry;
	char	*carry1;

	wchar = ft_strnew(bytes--);
	carry = handler_first_byte(wchar, unicode, bytes);
	if (bytes > 1)
	{
		bin = present_int_as_bin(unicode->b[1]);
		carry1 = ft_strsub(bin, 0, 4);
		ft_strdel(&bin);
		unicode->b[1] = unicode->b[1] << 2;
	}
	else
		unicode->b[1] = unicode->b[1] << 2;
	handler_sec_byte(wchar, unicode, --bytes, carry);
	if (bytes > 0)
		handler_third_byte(wchar, unicode, --bytes, carry1);
	if (bytes > 0)
		handler_fourth_byte(wchar, unicode, --bytes);
	return (wchar);
}
