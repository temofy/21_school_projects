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

long	*ft_atopi(const char *s)
{
	long	res;
	long	*p_result;
	int		i;
	int		sign;

	res = 0;
	i = 0;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-')
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (NULL);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (NULL);
		if (res > MAX_I || (res == MAX_I && (s[i] - '0') > 7 && sign == 1))
			return (NULL);
		if (res > MAX_I || (res == MAX_I && (s[i] - '0') > 8 && sign == -1))
			return (NULL);
		res = (res * 10) + s[i] - '0';
		i++;
	}
	res = res * sign;
	return (p_result = &res);
}
