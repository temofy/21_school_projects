/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strftchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:46:39 by cheller           #+#    #+#             */
/*   Updated: 2019/01/24 16:46:54 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strftchr(char *s, int pos, int c)
{
	char	*str;
	int		i;

	i = 0;
	s += pos;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			str = ft_strnew(i);
			str = ft_strncpy(str, s, i);
			return (str);
		}
		i++;
	}
	str = ft_strnew(ft_strlen(s));
	str = ft_strcpy(str, s);
	return (str);
}
