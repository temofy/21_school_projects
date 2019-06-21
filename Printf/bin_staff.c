/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:11:51 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/02 16:12:02 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		num_bin_len(long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / 2;
		i++;
	}
	return (i);
}

char	*bin_int(long int n)
{
	int			i;
	long int	*res;
	char		*c_res;
	long int	tmp;

	tmp = n;
	i = num_bin_len(n);
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int) * i))\
		|| !(c_res = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (--i >= 0)
	{
		res[i] = n % 2;
		n = n / 2;
	}
	i--;
	while (++i < num_bin_len(tmp))
		c_res[i] = (char)(res[i] + 48);
	free(res);
	return (c_res);
}

char	*bin_total(int n)
{
	char	*bin;

	if (n < 0)
	{
		bin = bin_int(4294967296 + (int)n);
		return (bin);
	}
	else
	{
		bin = bin_int((long)ft_abs(n));
		return (bin);
	}
}

char	*bin_total_l(long n)
{
	char	*bin;

	if (n < 0)
	{
		bin = bin_int(4294967296 + (long)n);
		return (bin);
	}
	else
	{
		bin = bin_int((long)ft_abs(n));
		return (bin);
	}
}
