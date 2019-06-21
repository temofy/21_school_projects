/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:05:57 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 15:06:13 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_oct_len(long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / 8;
		i++;
	}
	return (i);
}

char	*oct_int(long int n)
{
	int			i;
	long int	*res;
	char		*c_res;
	long int	tmp;

	tmp = n;
	i = num_oct_len(n);
	if (n == 0 && (c_res = (ft_strnew(1))))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int) * i))\
		|| !(c_res = ft_strnew(i)))
		return (NULL);
	while (--i >= 0)
	{
		res[i] = n % 8;
		n = n / 8;
	}
	while (++i < num_oct_len(tmp))
		c_res[i] = (char)(res[i] + 48);
	free(res);
	return (c_res);
}
