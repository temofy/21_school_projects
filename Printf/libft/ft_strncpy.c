/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:02:51 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 18:55:54 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;
	size_t		src_len;

	src_len = ft_strlen(src);
	index = 0;
	while (index < len)
	{
		if (index <= src_len)
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}
