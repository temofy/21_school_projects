/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_arithmetic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:06:52 by cheller           #+#    #+#             */
/*   Updated: 2019/05/05 21:01:40 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*t_long_value *sum(t_long_value *a, t_long_value *b)
 {
	t_long_value	*s;
	int				carry;
	int				i;
	
	if (a->length < b->length)
	{
		s = a;
		a = b;
		b = s;
	}
	i = 0;
	s = (t_long_value*)malloc(sizeof(t_long_value));
	s->length = a->length;
	s->values = (int*)malloc(sizeof(int) * s->length + 1);
 
	while (i < b->length)
	{
		s->values[i] = a->values[i] + b->values[i];
		s->values[i] += carry;
		carry = 0;
		if (s->values[i] >= 10)
		{
			carry = s->values[i] / 10;
			s->values[i] %= 10;
      	}
		i++;
	}
	while (i < a->length)
	{
		s->values[i] = a->values[i];
		s->values[i] += carry;
		carry = 0;
		if (s->values[i] >= 10)
		{
			carry = s->values[i] / 10;
			s->values[i] %= 10;
      	}
		i++;
	}
	if (carry > 0)
	{
		s->values[i] = carry;
		s->length += 1;
	}
	return (s);
}*/

void	PrintBigNum(t_long_value nbr)
{
	int   		i;
	signed char	leading_zeros;

	leading_zeros = 1;
	i = nbr.length - 1;
    while (i > -1)
	{
		/*if (nbr.values[i])
			leading_zeros = 0;
		if (!leading_zeros)*/
    		printf("%i", nbr.values[i]);
		i--;
	}
    printf("\n");
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
	/*printf("a: ");
	PrintBigNum(a);
	printf("b: ");
	PrintBigNum(b);*/
    s.length = a.length;
    s.values = (int*)malloc(sizeof(int) * s.length);
	ft_memcpy(s.values, a.values, a.length * 4);
    s.values[a.length] = 0;
	/*printf("s: ");
	PrintBigNum(s);*/
    for (i = 0; i < b.length; ++i) {
        s.values[i] = a.values[i] + b.values[i];
    }
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
	ft_memcpy(new_value, nbr.values, nbr.length);
	new_value[nbr.length] = 0;
	free(nbr.values);
	nbr.values = new_value;
	return (nbr);
}

void			normalize(t_long_value l) 
{
    int		i;
	int		carryover;

	i = -1;
    while (++i < l.length - 1) 
	{
        if (l.values[i] >= 10)
		{
            carryover = l.values[i] / 10;
			if (i + 1 < l.length - 1)
            	l.values[i + 1] += carryover;
			else
				l = ExpandValue(l);
            l.values[i] -= carryover * 10;
        } 
		else if (l.values[i] < 0)
		{
            int carryover = (l.values[i] + 1) / 10 - 1;
            l.values[i + 1] += carryover;
            l.values[i] -= carryover * 10;
        }
    }
}

t_long_value	naive_mul(t_long_value result, t_long_value a, t_long_value b)
{
	/*printf("naive a: ");
	PrintBigNum(a);
	printf("naive b: ");
	PrintBigNum(b);*/
	ft_memset(result.values, 0, sizeof(int) * result.length);
    for (int i = 0; i < a.length; ++i)
        for (int j = 0; j < b.length; ++j)
            result.values[i + j] += a.values[i] * b.values[j];
	return (result);
}
t_long_value karatsuba_mul(t_long_value a, t_long_value b) 
{
	//printf("done\n");
    t_long_value product;
    int i;

    product.length = a.length + b.length;
    product.values = malloc(sizeof(int) * product.length);
 
    if (a.length < 4)
		product = naive_mul(product, a, b);
    else 
	{ //умножение методом Карацубы
		/*printf("a: ");
		PrintBigNum(a);
		printf("b: ");
		PrintBigNum(b);*/
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
    //normalize(product);
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
	int				j;

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

t_long_value	ft_la_pow(t_long_value nbr, int exp)
{
	t_long_value	result;
	int				i;

	i = 0;
	result = karatsuba_mul(nbr, nbr);
	exp--;
	while (exp-- > 1)
	{
		result = karatsuba_mul(result, nbr);
	}
	return (result);
}


int		main()
{
    t_long_value  result;

	//result = karatsuba_mul(conv_to_la(999), conv_to_la(5));
	//result = ft_la_pow(conv_to_la(10), 60);
	result = sum(conv_to_la(99),conv_to_la(500001));
    //normalize(result);

    PrintBigNum(result);
    return (0);
}