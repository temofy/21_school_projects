/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_big_staff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:07:24 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 14:42:29 by aaeron-g         ###   ########.fr       */
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
	if (n == 0 && (c_res = ft_strnew(1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int) * i))\
		|| !(c_res = ft_strnew(i)))
		return (NULL);
	while (--i >= 0)
	{
		res[i] = n % 16;
		n = n / 16;
	}
	c_res = hexcimal_big(res, c_res, tmp);
	free(res);
	return (c_res);
}
