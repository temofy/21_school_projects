/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:24:58 by cheller           #+#    #+#             */
/*   Updated: 2018/12/21 13:35:57 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned		i;
	unsigned		len_s1;
	unsigned		len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = ft_strlen(s1);
	while (n-- && i < (len_s1 + len_s2))
	{
		s1[i] = s2[i - len_s1];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
