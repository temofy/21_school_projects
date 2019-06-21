/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:45:58 by cheller           #+#    #+#             */
/*   Updated: 2019/05/28 17:26:23 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		sub_without_neg(int a, int b)
{
	int result;

	result = a - b;
	if (result < 0)
		result = 0;
	return (result);
}

char	*handler_all_zeros(char **str, t_formatting *e_seq, int len)
{
	char *spaces;

	if (e_seq->precision > len)
	{
		spaces = ft_strnew_set('0', e_seq->precision - len);
		e_seq->width = sub_without_neg(e_seq->width, e_seq->precision - len);
		*str = ft_strfjoin(spaces, *str, 0);
	}
	if (!e_seq->flags->minus && e_seq->flags->zero && e_seq->precision == -1)
	{
		spaces = ft_strnew_set('0', e_seq->width);
		*str = ft_strfjoin(spaces, *str, 0);
		e_seq->width = 0;
	}
	if (e_seq->is_negative == 1)
		*str = ft_strfjoin("-", *str, 2);
	if (!e_seq->is_negative && e_seq->flags->plus)
		*str = ft_strfjoin("+", *str, 2);
	return (*str);
}

char	*handler_sequence_d(char **str, t_formatting *e_seq, char *spaces)
{
	int		length_str;

	if (e_seq->precision == 0 && **str == '0')
		*str = ft_strljoin(*str, ft_strnew(0), 0, 0);
	if (e_seq->width == -1)
		e_seq->width = 0;
	e_seq->width -= e_seq->is_negative;
	if (!e_seq->is_negative && e_seq->flags->plus)
		e_seq->width -= e_seq->flags->plus;
	if (!e_seq->flags->plus && !e_seq->is_negative)
		e_seq->width -= e_seq->flags->space;
	length_str = ft_strlen(*str);
	e_seq->width = sub_without_neg(e_seq->width, length_str);
	*str = handler_all_zeros(&*str, e_seq, length_str);
	spaces = ft_strnew_set(' ', e_seq->width);
	if (e_seq->flags->minus)
		*str = ft_strfjoin(*str, spaces, 0);
	else
		*str = ft_strfjoin(spaces, *str, 0);
	if (!e_seq->flags->plus && !e_seq->is_negative && e_seq->flags->space)
		*str = ft_strfjoin(" ", *str, 2);
	e_seq->common_length = ft_strlen(*str);
	return (*str);
}

char	*handler_d(va_list arg, t_formatting *e_seq)
{
	char	*nbr_str;
	char	*tmp;

	if (e_seq->length_modifier == 108)
		nbr_str = ft_litoa(va_arg(arg, long int));
	else if (e_seq->length_modifier == 216)
		nbr_str = ft_litoa(va_arg(arg, long long int));
	else if (e_seq->length_modifier == 104)
		nbr_str = ft_itoa((short int)va_arg(arg, int));
	else if (e_seq->length_modifier == 208)
		nbr_str = ft_itoa((signed char)va_arg(arg, int));
	else if (e_seq->length_modifier == 106)
		nbr_str = ft_litoa((intmax_t)va_arg(arg, intmax_t));
	else if (e_seq->length_modifier == 122)
		nbr_str = ft_litoa(va_arg(arg, size_t));
	else
		nbr_str = ft_itoa(va_arg(arg, int));
	if (*nbr_str == '-')
	{
		e_seq->is_negative = 1;
		tmp = ft_strdup(nbr_str + 1);
		free(nbr_str);
		nbr_str = tmp;
	}
	return (nbr_str = handler_sequence_d(&nbr_str, e_seq, NULL));
}
