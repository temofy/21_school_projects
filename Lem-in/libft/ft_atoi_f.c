/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atopi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:16:09 by cheller           #+#    #+#             */
/*   Updated: 2019/06/20 13:16:15 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		failed(int *flag)
{
	*flag = -1;
	return (0);
}

long	ft_atoi_f(const char *s, int *flag)
{
	long	res;
	int		i;
	int		sign;

	res = 0;
	if (!s)
		return (failed(0));
	i = 0;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (failed(flag));
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (failed(flag));
		if (res > MAX_I || (res == MAX_I && (s[i] - '0') > 7 && sign == 1))
			return (failed(flag));
		if (res > MAX_I || (res == MAX_I && (s[i] - '0') > 8 && sign == -1))
			return (failed(flag));
		res = (res * 10) + s[i] - '0';
		i++;
	}
	return (res * sign);
}
