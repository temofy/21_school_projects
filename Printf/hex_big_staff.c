/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_big_staff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:07:24 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/05/30 12:08:41 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*hexcimal_big(long int *res, char *c_res, long long int tmp)
{
	int	i;

	i = 0;
	while (i < num_hex_len(tmp))
	{
		if (res[i] < 10)
			c_res[i] = (char)(res[i] + 48);
		else
			c_res[i] = (char)(res[i] + 55);
		i++;
	}
	return (c_res);
}

char	*hex_int_big(long int n)
{
	int			i;
	long int	*res;
	char		*c_res;
	long int	tmp;
	char		*c_f_res;

	i = num_hex_len(n);
	tmp = n;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int) * i))\
		|| !(c_res = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (--i >= 0 && n / 16 <= tmp)
	{
		res[i] = n % 16;
		n = n / 16;
	}
	c_res = hexcimal_big(res, c_res, tmp);
	c_f_res = ft_sizedup(c_res, num_hex_len(tmp));
	return (c_f_res);
}

char	*hex_big_total_l(long int n)
{
	char	*hex;

	if (n < 0)
	{
		hex = hex_int_big(4294967296 + (unsigned long int)n);
		return ((hex + 1));
		free(hex);
	}
	else
	{
		hex = hex_int_big((long)ft_abs(n));
		return (hex);
		free(hex);
	}
}

char	*hex_big_total(long int n)
{
	char	*hex;

	if (n < 0)
	{
		hex = hex_int_big(4294967296 + (unsigned int)n);
		return ((hex + 1));
		free(hex);
	}
	else
	{
		hex = hex_int_big((long)ft_abs(n));
		return (hex);
		free(hex);
	}
}
