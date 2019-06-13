#include "ft_printf.h"

char	*handler_percent(t_formatting *e_seq)
{
	char	*str;
	int		str_len;

	str_len = handler_length(1, e_seq->width, 0);
	str = ft_strnew(str_len);
	ft_memset(str, ' ', str_len);
	e_seq->common_length += str_len + 1;
	if (e_seq->flags->minus)
		str = ft_strfjoin("%", str, 2);
	else
	{
		if (e_seq->flags->zero)
			str = ft_memset(str, '0', str_len);
		str = ft_strfjoin(str, "%", 1);
	}
	return (str);
}

char	*undefined_behavior(va_list arg, t_formatting *e_seq)
{
	char	*string;

	if (e_seq->specifier == 'Z')
	{
		string = ft_strnew(1);
		*string = 'Z';
	}
	e_seq->common_length = ft_strlen(string);
	return (string);
}

int		handler_length(int length, int width, int precision)
{
	if (length > width && length > precision)
		return (0);
	else if (length < width && length >= precision)
		return (width - length);
	else if (length >= width && length < precision)
		return (precision - length);
	else if (length < width && length < precision)
	{
		if (width > precision)
			return (width - length);
		else
			return (precision - length);
	}
	return (0);
}
