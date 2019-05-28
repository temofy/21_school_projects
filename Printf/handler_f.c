/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:00:01 by cheller           #+#    #+#             */
/*   Updated: 2019/05/20 20:17:27 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		for_round_int(t_str_fp **fp, char *nbr)
{
	int	len;
	int i;

	len = ft_strlen(nbr);
	i = 1;
	if (*nbr >= '6')
		return (1);
	else if (*nbr == '5')
	{
		while (i < len)
		{
			if (nbr[i] > '0')
				return (1);
			i++;
		}
		if (ft_iseven(ft_atoi((*fp)->integer)) == 0)
			return (1);
	}
	return (0);
}

int		overflow_frac(t_str_fp **fp, char *nbr, int pos)
{
	int		carry;

	carry = 0;
	if (pos == -1)
		return (for_round_int(&*fp, nbr));
	while (pos >= 0)
	{
		if (nbr[pos] == '9')
		{
			nbr[pos] = '0';
			carry = 1;
			pos--;
		}
		else if (carry > 0)
		{
			nbr[pos] += 1;
			carry = 0;
		}
		else
			return (0);
	}
	return (carry);
}

void	overflow_int(t_str_fp **fp, int carry)
{
	int pos;

	pos = ft_strlen((*fp)->integer) - 1;
	if (carry)
	{
		while (pos >= 0)
		{
			if ((*fp)->integer[pos] == '9')
			{
				(*fp)->integer[pos] = '0';
				carry = 1;
				pos--;
			}
			else if (carry > 0)
			{
				(*fp)->integer[pos] += 1;
				return ;
			}
		}
	}
	if (carry)
		(*fp)->integer = ft_strfjoin("1", (*fp)->integer, 2);
}

void	overflow_digit(t_str_fp **fp, int precision)
{
	int	carry;

	carry = overflow_frac(&*fp, (*fp)->frac, precision - 1);
	overflow_int(&*fp, carry);
}

char	*addition_zeros(char *nbr, int length)
{
	char	*zeros;

	if (!(zeros = ft_strnew(length)))
		return (NULL);
	ft_memset(zeros, 48, length);
	nbr = ft_strfjoin(nbr, zeros, 0);
	return (nbr);
}

void	round_frac(t_str_fp **str_fp, int precision)
{
	char	*rounded_nbr;
	int		i;
	size_t	len;

	len = ft_strlen((*str_fp)->frac);
	if (precision == -1)
		precision = 6;
	if (precision > len)
		(*str_fp)->frac = addition_zeros((*str_fp)->frac, precision - len);
	if (precision == 0)
	{
		overflow_digit(&*str_fp, precision);
		free((*str_fp)->frac);
		(*str_fp)->frac = ft_strdup("");
	}
	else if (((*str_fp)->frac[precision] - '0') < 5)
	{
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precision);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
	else if (((*str_fp)->frac[precision] - '0') > 6)
	{
		if ((*str_fp)->frac[precision - 1] < '9')
			(*str_fp)->frac[precision - 1] += 1;
		else
			overflow_digit(&*str_fp, precision);
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precision);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
	else
	{
		i = precision;
		while (++i < len)
		{
			if ((*str_fp)->frac[i] > '0')
			{
				if ((*str_fp)->frac[precision - 1] < '9')
					(*str_fp)->frac[precision - 1] += 1;
				else
					overflow_digit(&*str_fp, precision);
				rounded_nbr = ft_strsub((*str_fp)->frac, 0, precision);
				free((*str_fp)->frac);
				(*str_fp)->frac = rounded_nbr;
				return ;
			}
		}
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precision);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
}

char	*handler_sequence_f(char *str, t_formatting *e_seq, t_str_fp *str_fp)
{
	int		length;
	char	*spaces;

	spaces = ft_strnew(0);
	round_frac(&str_fp, e_seq->precision);
	if (e_seq->precision != 0)
	{
		str = ft_strjoin(str_fp->integer, ".");
		str = ft_strfjoin(str, str_fp->frac, 1);
	}
	else
		str = ft_strdup(str_fp->integer);
	length = ft_strlen(str);
	e_seq->width -= e_seq->is_negative;
	if (!e_seq->is_negative)
		e_seq->width -= e_seq->flags->plus;
	if (e_seq->width > length)
	{
		spaces = ft_strnew(e_seq->width - length);
		if (e_seq->flags->zero && !e_seq->flags->minus)
			ft_memset(spaces, '0', e_seq->width - length);
		else
			ft_memset(spaces, ' ', e_seq->width - length);
	}
	if (e_seq->flags->minus)
		str = ft_strfjoin(str, spaces, 0);
	else if (e_seq->flags->zero)
		str = ft_strfjoin(spaces, str, 0);
	if (e_seq->is_negative)
		str = ft_strfjoin("-", str, 2);
	else if (e_seq->flags->plus)
		str = ft_strfjoin("+", str, 2);
	if (!e_seq->flags->minus && !e_seq->flags->zero)
		str = ft_strfjoin(spaces, str, 0);
	return (str);
}

char	*handler_ambiguity(t_float *fp, char *str, t_formatting *e_seq)
{
	int		is_inf;
	int		i;
	int		width;
	char	*spaces;

	i = -1;
	is_inf = 1;
	while (++i < 64)
		if (fp->frac[i] == '1')
			is_inf = 0;
	if (is_inf)
		str = ft_strdup("inf");
	else
		str = ft_strdup("nan");
	if (is_inf && e_seq->is_negative)
		str = ft_strfjoin("-", str, 2);
	if (is_inf && e_seq->flags->plus && !e_seq->is_negative)
		str = ft_strfjoin("+", str, 2);
	width = e_seq->width - ft_strlen(str);
	spaces = ft_strnew(width);
	spaces = ft_memset(spaces, ' ', width);
	if (e_seq->flags->minus)
		str = ft_strfjoin(str, spaces, 0);
	else
		str = ft_strfjoin(spaces, str, 0);
	return (str);
}

t_float	*fill_fp(long double ldbl)
{
	t_float	*float_point;

	if (!(float_point = (t_float*)malloc(sizeof(t_float))))
		return (NULL);
	float_point->binary = (t_ld_nbr*)malloc(sizeof(t_ld_nbr));
	float_point->binary->ld = ldbl;
	float_point->binary_represent = represent_binary(float_point->binary->b);
	float_point->sign = *float_point->binary_represent;
	float_point->exp = ft_strsub(float_point->binary_represent, 1, 15);
	float_point->int_part = *(float_point->binary_represent + 16);
	float_point->frac = ft_strsub(float_point->binary_represent, 17, 63);
	return (float_point);
}

char	*handler_f(va_list arg, t_formatting *e_seq)
{
	char		*str;
	t_float		*fp;
	long double	ld;

	if (e_seq->length_modifier == 76)
		ld = (long double)va_arg(arg, long double);
	else
		ld = (long double)va_arg(arg, double);
	fp = fill_fp(ld);
	e_seq->is_negative = fp->sign - '0';
	str = get_number(fp, e_seq);
	free_fp(&fp);
	e_seq->common_length = ft_strlen(str);
	return (str);
}
