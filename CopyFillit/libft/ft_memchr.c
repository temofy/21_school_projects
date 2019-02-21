/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:49:23 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 14:43:26 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char*)s;
	while ((size_t)i < n)
	{
		if (ptr[i] == (char)c)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
