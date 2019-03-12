/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:00:55 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 14:04:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	calculate_len(int n, int base)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / base;
		len++;
	}
	return (len);
}

int		ft_abs(int nb)
{
	if (nb < 0)
		nb = -nb;
	return(nb);
}

char	*ft_itoa_base(int value, int base)
{
	char	*str;
	int		i;
	char	*tab;

	tab = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (0);
	i = calculate_len(value, base) - 1;
	str = (char*)malloc(sizeof(char) * calculate_len(value, base) + 1);

	if (value == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (value < 0 && base == 10)
	{
		str[0] = '-';
		value = value * -1;
	}
	str[i + 1] = '\0';
	while (value > 0)
	{
		str[i--] = tab[ft_abs(value % base)];
		value /= base;
	}
	return (str);
}
