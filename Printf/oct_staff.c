/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:32:57 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/05/30 12:42:53 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sizedup(const char *s, size_t n)
{
	unsigned int	i;
	char			*res;

	if ((res = (char*)malloc(sizeof(*res) * (n + 1))))
	{
		i = -1;
		while (*s && ++i < n)
			res[i] = s[i];
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

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
		res[i] = n % 8;
		n = n / 8;
	}
	i--;
	while (++i < num_oct_len(tmp))
		c_res[i] = (char)(res[i] + 48);
	free(res);
	return (c_res);
}

char	*oct_total(int n)
{
	char	*oct;

	if (n < 0)
	{
		oct = oct_int(4294967296 + (int)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}

char	*oct_total_l(long int n)
{
	char	*oct;

	if (n < 0)
	{
		oct = oct_int(4294967296 + (long int)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}
