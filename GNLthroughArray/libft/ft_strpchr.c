/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 14:57:43 by cheller           #+#    #+#             */
/*   Updated: 2019/02/10 13:46:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpchr(char *s, int c)
{
	char	*chr;
	size_t	i;

	i = 0;
	while (i < (ft_strlen(s)))
	{
		if (s[i] == (char)c)
		{
			if ((i + 1) < (ft_strlen(s)))
			{
				chr = &((char*)s)[i + 1];
				return (chr);
			}
		}
		i++;
	}
	return (NULL);
}
