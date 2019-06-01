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
	s = normalize(0, s);
	return (s);
}

t_long_value	expand_value(t_long_value nbr)
{
	int		*new_value;

	new_value = (int*)malloc(sizeof(int) * nbr.length + 1);
	new_value = ft_memcpy(new_value, nbr.values, nbr.length * sizeof(int));
	new_value[nbr.length] = 0;
	free(nbr.values);
	nbr.values = new_value;
	nbr.length++;
	return (nbr);
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
	product = normalize(0, product);
	return (product);
}

t_long_value	la_pow(t_long_value nbr, int exp)
{
	t_long_value	result;
	t_long_value	tmp;

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
	{
		tmp = result;
		result = karatsuba_mul(result, nbr);
		free(tmp.values);
	}
	free(nbr.values);
	return (result);
}
