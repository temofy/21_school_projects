#include "ft_printf.h"

char	*encode_one_byte(t_unicode *unicode)
{
	char	*wchar;

	wchar = ft_strnew(1);
	*wchar = unicode->chr;
	return (wchar);
}

char	*encode_two_bytes(t_unicode *unicode)
{
	char	*wchar;
	char 	*bin;
	char 	*carry;

	wchar = ft_strnew(2);
	bin = present_int_as_bin(unicode->b[0]);
	carry = ft_strsub(bin, 0, 2);
	bin = ft_strncpy(bin, "10", 2);
	wchar[1] = bin_as_dec(bin);
	free(bin);
	bin = present_int_as_bin(unicode->b[1]);
	bin = ft_strncpy(bin + 6, carry, 2);
	bin = bin - 6;
	bin = ft_strncpy(bin, "110", 3);
	wchar[0] = bin_as_dec(bin);
	return (wchar);
}

char	*encode_three_bytes(t_unicode *unicode)
{
	char	*wchar;
	char 	*bin;
	char 	*carry;
	char 	*carry1;

	wchar = ft_strnew(3);
	bin = present_int_as_bin(unicode->b[0]);
	carry = ft_strsub(bin, 0, 2);
	bin = ft_strncpy(bin, "10", 2);
	wchar[2] = bin_as_dec(bin);
	ft_strdel(&bin);
	//
	bin = present_int_as_bin(unicode->b[1]);
	carry1 = ft_strsub(bin, 0, 4);
	unicode->b[1] = unicode->b[1] << 2;
	bin = present_int_as_bin(unicode->b[1]);
	bin = ft_strncpy(bin + 6, carry, 2);
	bin = bin - 6;
	bin = ft_strncpy(bin, "10", 2);
	wchar[1] = bin_as_dec(bin);
	//
	bin = present_int_as_bin(unicode->b[2]);
	bin = ft_strncpy(bin + 4, carry1, 4);
	bin = bin - 4;
	bin = ft_strncpy(bin, "1110" , 4);
	wchar[0] = bin_as_dec(bin);
	free(bin);
	return (wchar);
}

char	*encode_four_bytes(t_unicode *unicode)
{
	char	*wchar;
	char 	*bin;
	char 	*carry;
	char 	*carry1;

	wchar = ft_strnew(3);
	bin = present_int_as_bin(unicode->b[0]);
	carry = ft_strsub(bin, 0, 2);
	bin = ft_strncpy(bin, "10", 2);
	wchar[3] = bin_as_dec(bin);
	ft_strdel(&bin);
	//
	bin = present_int_as_bin(unicode->b[1]);
	carry1 = ft_strsub(bin, 0, 4);
	unicode->b[1] = unicode->b[1] << 2;
	bin = present_int_as_bin(unicode->b[1]);
	bin = ft_strncpy(bin + 6, carry, 2);
	bin = bin - 6;
	bin = ft_strncpy(bin, "10", 2);
	wchar[2] = bin_as_dec(bin);
	//
	bin = present_int_as_bin(unicode->b[2]);
	bin = ft_strncpy(bin + 4, carry1, 4);
	bin = bin - 4;
	bin = ft_strncpy(bin, "1110" , 4);
	wchar[1] = bin_as_dec(bin);
	free(bin);
	//
	bin = present_int_as_bin(unicode->b[2]);
	carry = ft_strsub(bin, 3, 3);
	bin = ft_strncpy(bin + 5, carry, 3);
	bin = bin - 5;
	bin = ft_strncpy(bin, "11110" , 5);
	wchar[0] = bin_as_dec(bin);
	return (wchar);
}