/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:06:52 by cheller           #+#    #+#             */
/*   Updated: 2019/05/22 15:58:40 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

t_long_value	sum(t_long_value a, t_long_value b)
{
	t_long_value	s;
	int				i;

	i = -1;
	if (a.length < b.length)
	{
		s = a;
		a = b;
		b = s;
	}
	s.length = a.length;
	s.values = (int*)malloc(sizeof(int) * s.length);
	ft_memcpy(s.values, a.values, a.length * 4);
	s.values[a.length] = 0;
	while (++i < b.length)
		s.values[i] = a.values[i] + b.values[i];
	s = normalize(s);
	return (s);
}

t_long_value	expand_value(t_long_value nbr)
{
	int		*new_value;

	new_value = (int*)malloc(sizeof(int) * nbr.length + 1);
	ft_memcpy(new_value, nbr.values, nbr.length * sizeof(int));
	new_value[nbr.length] = 0;
	free(nbr.values);
	nbr.values = new_value;
	nbr.length++;
	return (nbr);
}

t_long_value	normalize(t_long_value l)
{
	int		i;
	int		carryover;

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

t_long_value	naive_mul(t_long_value result, t_long_value a, t_long_value b)
{
	int		i;
	int		j;

	i = 0;
	ft_memset(result.values, 0, sizeof(int) * result.length);
	while (i < a.length)
	{
		j = 0;
		while (j < b.length)
		{
			if ((i + j) > result.length - 1)
				result = expand_value(result);
			result.values[i + j] += a.values[i] * b.values[j];
			j++;
		}
		i++;
	}
	return (result);
}

t_long_value	karatsuba_mul(t_long_value a, t_long_value b)
{
	t_long_value	product;

	if (a.length > b.length)
		product.length = a.length;
	else
		product.length = b.length;
	product.values = malloc(sizeof(int) * product.length);
	if (a.length < 65)
		product = naive_mul(product, a, b);
	product = normalize(product);
	return (product);
}

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

t_long_value	la_pow(t_long_value nbr, int exp)
{
	t_long_value	result;

	if (exp == 0)
	{
		result.values = (int*)malloc(sizeof(int) * 1);
		result.values[0] = 1;
		result.length = 1;
		return (result);
	}
	if (exp == 1)
		return (nbr);
	result = karatsuba_mul(nbr, nbr);
	exp--;
	while (exp-- > 1)
		result = karatsuba_mul(result, nbr);
	return (result);
}
