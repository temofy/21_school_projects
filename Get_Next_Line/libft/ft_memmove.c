/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:07:11 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 17:49:18 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if (src <= dst)
		while (len--)
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
