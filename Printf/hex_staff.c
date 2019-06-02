/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:31:42 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/05/30 12:32:12 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*hexcimal(long long int *res, char *c_res, long long int tmp)
{
	int	i;

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

char	*hex_int(long int n)
{
	int				i;
	long long int	*res;
	char			*c_res;
	long long int	tmp;
	char			*c_f_res;

	i = num_hex_len(n);
	tmp = n;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long long int*)malloc(sizeof(long long int) * i))
		|| !(c_res = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	while (--i >= 0 && n / 16 <= tmp)
	{
		res[i] = n % 16;
		n = n / 16;
	}
	c_res = hexcimal(res, c_res, tmp);
	free(res);
	c_f_res = ft_sizedup(c_res, num_hex_len(tmp));
	free(c_res);
	return (c_f_res);
}

char	*hex_total(int n)
{
	char	*hex;

	if (n < 0)
	{
		hex = hex_int(4294967296 + (unsigned int)n);
		return ((hex + 1));
	}
	else
	{
		hex = hex_int((long)ft_abs(n));
		return (hex);
		free(hex);
	}
}

char	*hex_total_l(long long int n)
{
	char	*hex;

	if (n < 0)
	{
		hex = hex_int(4294967296 + (unsigned long long int)n);
		return ((hex + 1));
		free(hex);
	}
	else
	{
		hex = hex_int((long long)ft_abs(n));
		return (hex);
		free(hex);
	}
}
