/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:55:48 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 19:46:24 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char		*ptr;

	if (len == 0)
		return (b);
	ptr = (unsigned char*)b;
	while (len--)
	{
		*ptr = (unsigned char)c;
		if (len)
			ptr++;
	}
	return (b);
}
