/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 10:34:38 by cheller           #+#    #+#             */
/*   Updated: 2018/12/26 21:32:11 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		if (s[i] != (unsigned char)c)
			d[i] = s[i];
		else
		{
			d[i] = s[i];
			return (d + i + 1);
		}
		i++;
	}
	return (NULL);
}
