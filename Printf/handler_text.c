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
	int 	length_arg;
	int 	length_str;
	char 	*tmp;

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

char	*get_utf8_str(t_unicode *unicode)
{
	char	*wchar;

	if (unicode->chr <= 127)
		wchar = encode_one_byte(unicode);
	else if (unicode->chr <= 2047)
		wchar = encode_two_bytes(unicode);
	else if (unicode->chr <= 65535)
		wchar = encode_three_bytes(unicode);
	else if (unicode->chr <= 1114111)
		wchar = encode_four_bytes(unicode);
	return(wchar);
}

char 	*handler_chr_unicode(va_list arg, t_formatting *e_seq)
{
	//unsigned	unicode[1];
	char 		*binary;
	t_unicode	*unicode;
	char 		*str;

	unicode = (t_unicode*)malloc(sizeof(t_unicode));
	unicode->chr = va_arg(arg, unsigned int);
	binary = represent_binary(unicode->b, 4);
	binary = present_int_as_bin(unicode->b[0]);
	//str = get_utf8_str(binary, unicode->ld);
	printf("binary: %s\n", binary);

	//e_seq->common_length = 4;
	//str = ft_strdup("\xF0\x90\x8D\x88");
	return (str);
}

/*char 	*handler_chr_unicode(va_list arg, t_formatting *e_seq)
{
	unsigned	unicode[1];
	char 		*str;
	t_unicode	*ucode;

	//ucode = (t_unicode*)malloc(sizeof(t_unicode));
	unicode[0] = va_arg(arg, unsigned int);
	//str = represent_binary(ucode->b, 4);
	//printf("binary: %s\n", str);
	str = ft_strnew(1);
	str = ft_memcpy(str, unicode, 1);
	e_seq->common_length = 4;
	str = ft_strdup("\xF0\x90\x8D\x88");
	return (str);
}*/

char 	*handler_str_unicode(va_list arg, t_formatting *e_seq)
{
	unsigned int	unicode;

	unicode = va_arg(arg, unsigned int);

	return (NULL);
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
