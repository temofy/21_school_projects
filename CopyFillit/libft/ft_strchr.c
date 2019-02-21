/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:43:10 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 15:03:12 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*chr;
	size_t	i;

	i = -1;
	while (++i < (ft_strlen(s) + 1))
	{
		if (s[i] == (char)c)
		{
			chr = &((char*)s)[i];
			return (chr);
		}
	}
	return (NULL);
}
