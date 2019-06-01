/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 13:43:15 by cheller           #+#    #+#             */
/*   Updated: 2019/06/01 13:43:20 by cheller          ###   ########.fr       */
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

void	round_more_five(char **rounded_nbr, t_str_fp **str_fp, int prec)
{
	if ((*str_fp)->frac[prec - 1] < '9')
		(*str_fp)->frac[prec - 1] += 1;
	else
		overflow_digit(&*str_fp, prec);
	*rounded_nbr = ft_strsub((*str_fp)->frac, 0, prec);
	free((*str_fp)->frac);
	(*str_fp)->frac = *rounded_nbr;
}

void	round_five(char **rounded_nbr, t_str_fp **str_fp, int prec, int len)
{
	int	i;

	i = prec;
	while (++i < len)
	{
		if ((*str_fp)->frac[i] > '0')
		{
			if ((*str_fp)->frac[prec - 1] < '9')
				(*str_fp)->frac[prec - 1] += 1;
			else
				overflow_digit(&*str_fp, prec);
			*rounded_nbr = ft_strsub((*str_fp)->frac, 0, prec);
			free((*str_fp)->frac);
			(*str_fp)->frac = *rounded_nbr;
			return ;
		}
	}
	*rounded_nbr = ft_strsub((*str_fp)->frac, 0, prec);
	free((*str_fp)->frac);
	(*str_fp)->frac = *rounded_nbr;
}

void	round_frac(t_str_fp **str_fp, int precision)
{
	char	*rounded_nbr;
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
		round_more_five(&rounded_nbr, &*str_fp, precision);
	else
		round_five(&rounded_nbr, &*str_fp, precision, len);
}
