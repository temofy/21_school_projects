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
#include <stdio.h>

void	OverflowDigit(char *nbr, int pos)
{
	int		carry;

	carry = 0;
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
			return ;
	}
}

char	*AdditionZeros(char *nbr, int length)
{
	char	*zeros;

	if (!(zeros = ft_strnew(length)))
		return (NULL);
	memset(zeros, 48, length);
	nbr = ft_strfjoin(nbr, zeros, 0);
	return (nbr);
}

void	RoundFracPart(t_str_fp **str_fp, int precsion)
{
	char	*rounded_nbr;
	int		i;
	size_t	len;

	len = ft_strlen((*str_fp)->frac);
	if (precsion == -1)
		precsion = 6;
	if (precsion > len)
		(*str_fp)->frac = AdditionZeros((*str_fp)->frac, precsion - len);
	if (precsion == 0)
	{
		free((*str_fp)->frac);
		(*str_fp)->frac = ft_strdup("");
	}
	else if (((*str_fp)->frac[precsion] - '0') < 5)
	{
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precsion);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
	else if (((*str_fp)->frac[precsion] - '0') > 6)
	{
		if ((*str_fp)->frac[precsion - 1] < '9')
			(*str_fp)->frac[precsion - 1] += 1;
		else
			OverflowDigit((*str_fp)->frac, precsion - 1);
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precsion);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
	else
	{
		i = precsion;
		while (++i < len)
		{
			if ((*str_fp)->frac[i] > '0')
			{
				if ((*str_fp)->frac[precsion - 1] < '9')
					(*str_fp)->frac[precsion - 1] += 1;
				else
					OverflowDigit((*str_fp)->frac, precsion - 1);
				rounded_nbr = ft_strsub((*str_fp)->frac, 0, precsion);
				free((*str_fp)->frac);
				(*str_fp)->frac = rounded_nbr;
				return ;
			}
		}
		rounded_nbr = ft_strsub((*str_fp)->frac, 0, precsion);
		free((*str_fp)->frac);
		(*str_fp)->frac = rounded_nbr;
	}
}

char	*handler_sequence_f(char *str, t_formatting *e_seq, t_str_fp *str_fp)
{
	int		length;
	char	*spaces;

	spaces = ft_strnew(0);
	RoundFracPart(&str_fp, e_seq->precision);
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

t_float	*Fill_FP(long double Ldbl)
{
	t_float	*float_point;

	if (!(float_point = (t_float*)malloc(sizeof(t_float))))
		return (NULL);
	float_point->binary = (t_ld_nbr*)malloc(sizeof(t_ld_nbr));
	float_point->binary->ld = Ldbl;
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
	fp = Fill_FP(ld);
	e_seq->is_negative = fp->sign - '0';
	str = get_number(fp, e_seq);
	free_fp(&fp);
	e_seq->common_length = ft_strlen(str);
	return (str);
}
