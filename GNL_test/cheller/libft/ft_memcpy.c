/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V2.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 19:15:04 by cheller           #+#    #+#             */
/*   Updated: 2018/12/26 20:02:40 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pd;
	char	*ps;

	if (!dst && !src)
		return (NULL);
	if (n == 0 || dst == src)
		return (dst);
	pd = (char *)dst;
	ps = (char *)src;
	while (--n)
		*pd++ = *ps++;
	*pd = *ps;
	return (dst);
}
