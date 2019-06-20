/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:39:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/02 16:11:48 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Downloads/hopb_without_leaks/ft_printf.h"

char	*bin_zero(t_formatting *e_sequence, int *len, char *res)
{
	*len = -1;
	if (e_sequence->flags->minus && e_sequence->flags->hash)
	{
		res = ft_strdup("0");
		*len = *len + 1;
	}
	else if (e_sequence->flags->hash == 1)
	{
		*len = *len + 1;
		res = ft_strdup("0");
	}
	else
		res = ft_strdup(" ");
	while (++(*len) < e_sequence->width)
		res = ft_strfjoin(res, " ", 1);
	if (e_sequence->flags->hash == 1)
		res = ft_strfjoin(res, "0", 1);
	e_sequence->common_length += *len;
	return (res);
}

char	*bin_not_zero(t_formatting *e_sequence, int *len, char *res, char *bin)
{
	if (e_sequence->flags->hash == 1 && !ft_strequ(bin, "0"))
	{
		res = ft_strfjoin("0", res, 2);
		*len = *len + 1;
	}
	while (*len < e_sequence->width)
	{
		res = ft_strfjoin("0", res, 2);
		*len = ft_strlen(res);
	}
	return (res);
}

char	*bin_while(t_formatting *e_sequence, int *len, char *res)
{
	while (*len < e_sequence->width)
	{
		res = ft_strfjoin(" ", res, 2);
		*len = ft_strlen(res);
	}
	return (res);
}

char	*bin_else(t_formatting *e_sequence, int *len, char *res, char *bin)
{
	while (*len < e_sequence->precision)
	{
		res = ft_strfjoin("0", res, 2);
		*len = ft_strlen(res);
	}
	if (e_sequence->flags->hash == 1 && !ft_strequ(bin, "0"))
	{
		res = ft_strfjoin("0", res, 2);
		*len = *len + 1;
	}
	if (e_sequence->flags->minus == 1)
	{
		while (*len < e_sequence->width)
		{
			res = ft_strfjoin(res, " ", 1);
			*len = ft_strlen(res);
		}
	}
	else
		res = bin_while(e_sequence, len, res);
	return (res);
}

char	*handler_b(va_list arg, t_formatting *e_sequence)
{
	char	*bin;
	char	*res;
	int		len;

	if (e_sequence->length_modifier == 108 ||\
	e_sequence->length_modifier == 216)
		bin = bin_total_l((intmax_t)va_arg(arg, void *));
	else
		bin = bin_total((int)va_arg(arg, void *));
	if (ft_strequ(bin, "0") && e_sequence->precision == 0)
	{
		res = bin_zero(e_sequence, &len, res);
		return (res);
	}
	res = bin;
	len = ft_strlen(bin);
	if (e_sequence->precision <= 0 && e_sequence->flags->minus == 0\
	&& e_sequence->flags->zero == 1)
		res = bin_not_zero(e_sequence, &len, res, bin);
	else
		res = bin_else(e_sequence, &len, res, bin);
	ft_strdel(&bin);
	e_sequence->common_length += len;
	return (res);
}
