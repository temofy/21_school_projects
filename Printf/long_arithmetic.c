/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:06:52 by cheller           #+#    #+#             */
/*   Updated: 2019/05/06 15:54:52 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *ConvBigNumToStr(t_long_value nbr)
{
    char    *frac;
    int     i;
    int     k;

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


t_long_value sum(t_long_value a, t_long_value b) 
{
    t_long_value s;
    int i;

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
    for (i = 0; i < b.length; ++i) {
        s.values[i] = a.values[i] + b.values[i];
    }
    s = normalize(s);
    return s;
}
 
t_long_value	sub(t_long_value a, t_long_value b)
{
	int		i;

	i = -1;
    while (++i < b.length)
        a.values[i] -= b.values[i];
    return (a);
}

t_long_value	ExpandValue(t_long_value nbr)
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

t_long_value		normalize(t_long_value l)
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
            else {
                l = ExpandValue(l);
                l.values[i + 1] += carryover;
            }
            l.values[i] -= carryover * 10;
        } 
		else if (l.values[i] < 0)
		{
            int carryover = (l.values[i] + 1) / 10 - 1;
            l.values[i + 1] += carryover;
            l.values[i] -= carryover * 10;
        }
    }
    return (l);
}

t_long_value	naive_mul(t_long_value result, t_long_value a, t_long_value b)
{
	ft_memset(result.values, 0, sizeof(int) * result.length);
    for (int i = 0; i < a.length; ++i)
        for (int j = 0; j < b.length; ++j)
		{
			if ((i + j) > result.length - 1)
				result = ExpandValue(result);
            result.values[i + j] += a.values[i] * b.values[j];
		}
	return (result);
}
t_long_value karatsuba_mul(t_long_value a, t_long_value b)
{
    t_long_value product;
    int i;

	if (a.length > b.length)
    	product.length = a.length;
	else
		product.length = b.length;
    product.values = malloc(sizeof(int) * product.length);
 
    if (a.length < 65)
		product = naive_mul(product, a, b);
    else 
	{
        t_long_value a_part1; //младшая часть числа a
        a_part1.values = a.values;
        a_part1.length = (a.length + 1) / 2;
 
        t_long_value a_part2; //старшая часть числа a
        a_part2.values = a.values + a_part1.length;
        a_part2.length = a.length / 2;
 
        t_long_value b_part1; //младшая часть числа b
        b_part1.values = b.values;
        b_part1.length = (b.length + 1) / 2;
 
        t_long_value b_part2; //старшая часть числа b
        b_part2.values = b.values + b_part1.length;
        b_part2.length = b.length / 2;
 
        t_long_value sum_of_a_parts = sum(a_part1, a_part2); //cумма частей числа a
        normalize(sum_of_a_parts);
        t_long_value sum_of_b_parts = sum(b_part1, b_part2); //cумма частей числа b
        normalize(sum_of_b_parts);
        t_long_value product_of_sums_of_parts = karatsuba_mul(sum_of_a_parts, sum_of_b_parts);
        // произведение сумм частей
 
        t_long_value product_of_first_parts = karatsuba_mul(a_part1, b_part1); //младший член
        t_long_value product_of_second_parts = karatsuba_mul(a_part2, b_part2); //старший член
        t_long_value sum_of_middle_terms = sub(sub(product_of_sums_of_parts, product_of_first_parts), product_of_second_parts);
        //нахождение суммы средних членов
 
        ft_memcpy(product.values, product_of_first_parts.values,
               product_of_first_parts.length * sizeof(int));
        ft_memcpy(product.values + product_of_first_parts.length,
               product_of_second_parts.values, product_of_second_parts.length * sizeof(int));
        for (i = 0; i < sum_of_middle_terms.length; ++i)
            product.values[a_part1.length + i] += sum_of_middle_terms.values[i];
        free(sum_of_a_parts.values);
        free(sum_of_b_parts.values);
        free(product_of_sums_of_parts.values);
        free(product_of_first_parts.values);
        free(product_of_second_parts.values);
    }
    product = normalize(product);
    return product;
}

int	nbr_len(signed long n)
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
	{
		result = karatsuba_mul(result, nbr);
	}
	return (result);
}
