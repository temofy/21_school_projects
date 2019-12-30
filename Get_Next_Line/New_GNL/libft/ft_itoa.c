/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:37:14 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 14:58:53 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int n)
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

static char	*ft_negative_max(char *str, int n)
{
	n = n + 1;
	str = ft_itoa(n);
	str[10] = '8';
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = nbr_len(n) - 1;
	str = ft_strnew(nbr_len(n));
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return (ft_negative_max(str, n));
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
