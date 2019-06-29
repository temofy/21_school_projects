/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:43:10 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 18:57:48 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*chr;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	i = -1;
	while (++i < (s_len + 1))
	{
		if (s[i] == (char)c)
		{
			chr = &((char*)s)[i];
			return (chr);
		}
	}
	return (NULL);
}
