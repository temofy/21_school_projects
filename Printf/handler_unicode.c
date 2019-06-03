#include "ft_printf.h"

char	*encode_one_byte(t_unicode *unicode)
{
	char	*wchar;

	return (wchar);
}

char	*encode_two_bytes(t_unicode *unicode)
{
	char	*wchar;
	char 	*carry;
	int 	i;

	wchar = present_int_as_bin(unicode->b[0]);
	carry = ft_strsub(wchar, 0, 2);
	return (wchar);
}

char	*encode_three_bytes(t_unicode *unicode)
{
	char	*wchar;
	return (wchar);
}

char	*encode_four_bytes(t_unicode *unicode)
{
	char	*wchar;
	return (wchar);
}