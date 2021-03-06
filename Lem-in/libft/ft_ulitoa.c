/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:26:56 by cheller           #+#    #+#             */
/*   Updated: 2019/04/12 21:15:12 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(unsigned long n)
{
	int		len;

	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_ulitoa(unsigned long long int n)
{
	char	*str;
	int		i;

	i = nbr_len(n) - 1;
	if (!(str = ft_strnew(nbr_len(n))))
		return (NULL);
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (n > 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}
