/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_unicode_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 12:25:19 by cheller           #+#    #+#             */
/*   Updated: 2019/06/21 12:25:21 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_utf8_str(t_unicode *unicode)
{
	char	*wchar;

	if (unicode->chr <= 127)
	{
		wchar = ft_strnew(1);
		*wchar = unicode->chr;
	}
	else if (unicode->chr <= 2047)
		wchar = encode_bytes(unicode, 2);
	else if (unicode->chr <= 65535)
		wchar = encode_bytes(unicode, 3);
	else if (unicode->chr <= 1114111)
		wchar = encode_bytes(unicode, 4);
	return (wchar);
}

char	*combine_str_unicode(unsigned *str_unicode, t_unicode **unicode)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	*unicode = (t_unicode *)malloc(sizeof(t_unicode));
	len = ft_intlen(str_unicode);
	str = ft_strnew(0);
	while (++i < len)
	{
		(*unicode)->chr = str_unicode[i];
		str = ft_strfjoin(str, get_utf8_str(*unicode), 0);
	}
	free(*unicode);
	return (str);
}

char	*handler_chr_unicode(va_list arg, t_formatting *e_seq)
{
	t_unicode		*unicode;
	char			*str;
	int				len_str;
	int				len_spaces;
	char			*spaces;

	unicode = (t_unicode*)malloc(sizeof(t_unicode));
	unicode->chr = va_arg(arg, unsigned int);
	str = get_utf8_str(unicode);
	len_str = ft_strlen(str);
	if (unicode->chr == 0)
		len_str++;
	len_spaces = handler_length(len_str, e_seq->width, 0);
	spaces = ft_strnew(len_spaces);
	if (e_seq->flags->zero && !e_seq->flags->minus)
		ft_memset(spaces, '0', len_spaces);
	else
		ft_memset(spaces, ' ', len_spaces);
	e_seq->common_length = len_spaces + len_str;
	if (!e_seq->flags->minus)
		str = ft_strljoin(spaces, str, len_spaces, len_str);
	else
		str = ft_strljoin(str, spaces, len_str, len_spaces);
	free(unicode);
	return (str);
}

char	*handler_str_unicode(va_list arg, t_formatting *e_seq)
{
	unsigned	*str_unicode;
	t_unicode	*unicode;
	char		*str;
	char		*spaces;

	str_unicode = va_arg(arg, unsigned int*);
	if (str_unicode == NULL)
		str = ft_strdup("(null)");
	else
		str = combine_str_unicode(str_unicode, &unicode);
	str = handler_sequence_s(str, &spaces, e_seq);
	e_seq->common_length = ft_strlen(str);
	return (str);
}
