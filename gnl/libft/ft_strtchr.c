/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:48:50 by cheller           #+#    #+#             */
/*   Updated: 2019/02/11 21:10:18 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtchr(char *s, int c)
{
	char	*str;
	int		i;

	i = -1;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
	{
		str = ft_strnew(i);
		str = ft_strncpy(str, s, i);
		return (str);
	}
	/*while (++i < (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
		str = ft_strnew(i);
			str = ft_strncpy(str, s, i);
			return (str);
		}
	}*/
	return (NULL);
}
