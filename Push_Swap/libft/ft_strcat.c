/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:19:07 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 15:02:44 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	lens1;

	lens1 = ft_strlen(s1);
	i = ft_strlen(s1);
	while (i < (lens1 + ft_strlen(s2)))
	{
		s1[i] = s2[i - lens1];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
