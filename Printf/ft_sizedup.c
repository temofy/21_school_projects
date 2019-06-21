/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizedup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:03:59 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 15:04:39 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sizedup(const char *s, size_t n)
{
	unsigned int	i;
	char			*res;

	if ((res = ft_strnew(n)))
	{
		i = -1;
		while (*s && ++i < n)
			res[i] = s[i];
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
