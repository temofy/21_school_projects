/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:02:51 by cheller           #+#    #+#             */
/*   Updated: 2019/01/14 16:04:11 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;

	index = 0;
	while (index < len)
	{
		if (index <= (size_t)ft_strlen(src))
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}
