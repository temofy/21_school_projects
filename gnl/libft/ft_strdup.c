/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 13:15:19 by cheller           #+#    #+#             */
/*   Updated: 2019/02/12 19:53:34 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*str;

	str = NULL;
	if (src == NULL)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	if (!(str = (char*)malloc(sizeof(char) * (len +1))))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}
