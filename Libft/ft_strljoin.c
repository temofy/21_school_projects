/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:39:07 by cheller           #+#    #+#             */
/*   Updated: 2019/04/09 14:33:28 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strljoin(char *s1, char *s2, int len1, int len2)
{
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(str = ft_strnew(len1 + len2)))
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	free(s1);
	free(s2);
	return (str);
}
