/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:20:41 by cheller           #+#    #+#             */
/*   Updated: 2019/05/28 13:20:45 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				nbr_len(signed long n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

t_long_value	conv_to_la(signed long nbr)
{
	t_long_value	result;
	int				*value;
	int				i;

	result.length = nbr_len(nbr);
	value = (int*)malloc(sizeof(int) * result.length);
	result.values = value;
	i = 0;
	while (i < result.length)
	{
		result.values[i] = nbr % 10;
		nbr /= 10;
		i++;
	}
	return (result);
}

char			*conv_bignum_to_str(t_long_value nbr)
{
	char	*frac;
	int		i;
	int		k;

	k = 0;
	i = nbr.length - 1;
	frac = ft_strnew(nbr.length);
	while (i > -1)
	{
		frac[k++] = nbr.values[i] + '0';
		i--;
	}
	return (frac);
}

t_long_value	normalize(int carryover, t_long_value l)
{
	int		i;

	i = -1;
	while (++i < l.length)
	{
		if (l.values[i] >= 10)
		{
			carryover = l.values[i] / 10;
			if (i + 1 < l.length)
				l.values[i + 1] += carryover;
			else
			{
				l = expand_value(l);
				l.values[i + 1] += carryover;
			}
			l.values[i] -= carryover * 10;
		}
		else if (l.values[i] < 0)
		{
			carryover = (l.values[i] + 1) / 10 - 1;
			l.values[i + 1] += carryover;
			l.values[i] -= carryover * 10;
		}
	}
	return (l);
}
