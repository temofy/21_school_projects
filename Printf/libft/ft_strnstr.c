/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:38:59 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 16:29:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hys, const char *need, size_t len)
{
	if (ft_strlen(need) == 0)
		return ((char*)hys);
	while (*hys != '\0' && len-- >= ft_strlen(need))
	{
		if (*hys == *need && ft_memcmp(hys, need, ft_strlen(need)) == 0)
			return ((char*)hys);
		hys++;
	}
	return (NULL);
}
