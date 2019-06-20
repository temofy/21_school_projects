/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 11:56:41 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 14:48:19 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Downloads/hopb_without_leaks/ft_printf.h"
#include <limits.h>

char	*oct_zero(t_formatting *e_sequence, int *len, char *res)
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

char	*oct_not_zero(t_formatting *e_sequence, int *len, char *res, char *oct)
{
	if (e_sequence->flags->hash == 1 && !ft_strequ(oct, "0"))
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

char	*oct_while(t_formatting *e_sequence, int *len, char *res)
{
	while (*len < e_sequence->width)
	{
		res = ft_strfjoin(" ", res, 2);
		*len = ft_strlen(res);
	}
	return (res);
}

char	*oct_else(t_formatting *e_sequence, int *len, char *res, char *oct)
{
	while (*len < e_sequence->precision)
	{
		res = ft_strfjoin("0", res, 2);
		*len = ft_strlen(res);
	}
	if (e_sequence->flags->hash == 1 && !ft_strequ(oct, "0"))
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
		res = oct_while(e_sequence, len, res);
	return (res);
}

char	*handler_o(va_list arg, t_formatting *e_sequence)
{
	char	*oct;
	char	*res;
	int		len;

	if (e_sequence->length_modifier == 106 ||\
	e_sequence->length_modifier == 108 || e_sequence->length_modifier == 216)
		oct = oct_total_l((long int)va_arg(arg, void *));
	else
		oct = oct_total((int)va_arg(arg, void *), e_sequence);
	if (ft_strequ(oct, "0") && e_sequence->precision == 0)
	{
		res = oct_zero(e_sequence, &len, res);
		return (res);
	}
	res = ft_strdup(oct);
	len = ft_strlen(oct);
	if (e_sequence->precision <= 0 && e_sequence->flags->minus == 0\
		&& e_sequence->flags->zero == 1)
		res = oct_not_zero(e_sequence, &len, res, oct);
	else
		res = oct_else(e_sequence, &len, res, oct);
	e_sequence->common_length += len;
	free(oct);
	return (res);
}
