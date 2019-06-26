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

long	*ft_atopi(const char *str)
{
	long	result;
	long	*p_result;
	int		i;
	int		sign;

	result = 0;
	i = 0;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (NULL);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (NULL);
		if (result > PRE_MAX_INT ||	(result == PRE_MAX_INT && (str[i] - '0') > 7 && sign == 1))
			return (NULL);
		if (result > PRE_MAX_INT ||	(result == PRE_MAX_INT && (str[i] - '0') > 8 && sign == -1))
			return (NULL);
		result = (result * 10) + str[i] - '0';
		i++;
	}
	result = result * sign;
	return (p_result = &result);
}
