/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:57:43 by cheller           #+#    #+#             */
/*   Updated: 2019/02/13 15:31:15 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpchr(char *s, int c)
{
	char	*chr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	while (s[i] != (char)c && i < len)
		i++;
	if (s[i] == (char)c)
	{
		if ((i + 1) < len)
		{
			chr = &((char*)s)[i + 1];
			return (chr);
		}
	}
	return (NULL);
}
