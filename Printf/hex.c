/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:50:21 by cheller           #+#    #+#             */
/*   Updated: 2019/06/19 18:01:35 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_hex_len(unsigned long long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*hex(int *res, char *c_res, long int tmp)
{
	int i;

	i = 0;
	while (i < num_hex_len(tmp))
	{
		if (res[i] < 10)
			c_res[i] = (char)(res[i] + 48);
		else
			c_res[i] = (char)(res[i] + 87);
		i++;
	}
	return (c_res);
}

char	*hex_long_int(long int n)
{
	int			i;
	int			*res;
	char		*c_res;
	long int	tmp;

	tmp = n;
	i = num_hex_len(n);
	if (n == 0 && (c_res = ft_strnew(1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (int*)malloc(sizeof(long int) * i)) \
		|| !(c_res = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (--i >= 0)
	{
		res[i] = n % 16;
		n = n / 16;
	}
	c_res = hex(res, c_res, tmp);
	free(res);
	return (c_res);
}
