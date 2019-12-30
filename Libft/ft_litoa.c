/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:37:14 by cheller           #+#    #+#             */
/*   Updated: 2019/04/16 15:39:30 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long long int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_negative_max(char **str)
{
	*str = ft_strnew(20);
	ft_memcpy(*str, "-9223372036854775808", 20);
	return (*str);
}

char		*ft_litoa(long long int n)
{
	char	*str;
	int		i;

	if (n == -9223372036854775807 - 1)
		return (ft_negative_max(&str));
	i = nbr_len(n) - 1;
	str = ft_strnew(i + 1);
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}
