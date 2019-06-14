/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   represents.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 19:55:39 by cheller           #+#    #+#             */
/*   Updated: 2019/05/20 20:16:36 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*present_int_as_bin(unsigned char number)
{
	char	*bin;
	int		i;

	i = 8;
	bin = ft_strnew(8);
	while (i--)
	{
		*bin = ((number >> i) & 1) + '0';
		bin++;
	}
	return (bin - 8);
}

char			*represent_binary(unsigned char *bytes, int nbr_bytes)
{
	char	*binary;
	int		i;
	int		j;

	i = 0;
	j = nbr_bytes - 1;
	if (!(binary = ft_strnew(nbr_bytes * 8)))
		return (NULL);
	while (i++ < nbr_bytes)
		binary = ft_strfjoin(binary, present_int_as_bin(bytes[j--]), 0);
	return (binary);
}

unsigned long	bin_as_dec(char *bin)
{
	unsigned long	decimal;
	unsigned long	factor;
	size_t			len;

	factor = 1;
	len = ft_strlen(bin);
	decimal = 0;
	while (len--)
	{
		if (bin[len] == '1')
		{
			decimal += 1 * factor;
		}
		factor *= 2;
	}
	return (decimal);
}
