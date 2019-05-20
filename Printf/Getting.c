/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:00:42 by cheller           #+#    #+#             */
/*   Updated: 2019/05/20 20:33:56 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_decimal_int_str(char *bin)
{
	char	*str;

	str = ft_ulitoa((unsigned long long)bin_as_dec(bin));
	free(bin);
	return (str);
}

t_str_fp	*get_decimal_frac_str(char *frac_bin, t_str_fp *str)
{
	int				i;
	size_t			len;
	t_long_value	tmp;
	t_long_value	result;
	t_long_value	decade_in_exp;

	result.values = (int*)malloc(sizeof(int) * 1);
	result.values[0] = 0;
	result.length = 0;
	i = 0;
	len = ft_strlen(frac_bin);
	while (i < len)
	{
		if (frac_bin[i] == '1')
		{
			decade_in_exp = la_pow(conv_to_la(10), len - i - 1);
			tmp = karatsuba_mul((la_pow(conv_to_la(5), i + 1)), decade_in_exp);
			result = sum(result, tmp);
			free(tmp.values);
		}
		i++;
	}
	free(str->frac);
	str->frac = ConvBigNumToStr(result);
	return (str);
}

char		*get_lz(int amount)
{
	char	*leading_zeros;

	leading_zeros = strdup("");
	if (amount == 0)
		return (leading_zeros);
	while (amount--)
		leading_zeros = ft_strfjoin("0", leading_zeros, 2);
	return (leading_zeros);
}

char		*get_frac_zeros(long double nbr)
{
	int		zeros;
	int		integer;
	char	*str_zeros;

	if (!nbr)
		return (ft_strnew(0));
	nbr -= (int)nbr;
	integer = nbr;
	if (integer || nbr == 0.0)
		return (ft_strdup(""));
	zeros = 0;
	while (!integer)
	{
		nbr = nbr * 10;
		integer = (int)nbr;
		zeros++;
	}
	zeros--;
	str_zeros = ft_strnew(zeros);
	str_zeros = ft_memset(str_zeros, 48, zeros);
	return (str_zeros);
}

char		*get_number(t_float *fp, t_formatting *e_seq)
{
	int			exp;
	t_str_fp	*s_fp;
	char		*str;

	s_fp = (t_str_fp*)malloc(sizeof(t_str_fp));
	if ((exp = (bin_as_dec(fp->exp) - 16383)) == 16384)
		return (handler_ambiguity(fp, str, e_seq));
	if (exp >= 0)
	{
		s_fp->integer = ft_strdup(&fp->int_part);
		s_fp->integer = ft_strjoin(s_fp->integer, ft_strsub(fp->frac, 0, exp));
		s_fp->frac = ft_strsub(fp->frac, exp, 63 - exp);
	}
	else
	{
		s_fp->integer = ft_strdup("0");
		s_fp->frac = ft_strjoin(&fp->int_part, fp->frac);
		s_fp->frac = ft_strfjoin(get_lz(ft_abs(exp + 1)), s_fp->frac, 0);
	}
	s_fp = get_decimal_frac_str(s_fp->frac, s_fp);
	s_fp->integer = get_decimal_int_str(s_fp->integer);
	s_fp->frac = ft_strfjoin(get_frac_zeros(fp->binary->ld), s_fp->frac, 2);
	str = handler_sequence_f(str, e_seq, s_fp);
	free_str_fp(&s_fp);
	return (str);
}
