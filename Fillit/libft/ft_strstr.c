/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:26:36 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 15:52:25 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hys, const char *need)
{
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(need) == 0)
		return ((char*)hys);
	while (hys[i])
	{
		j = 0;
		while (need[j] == hys[i + j])
		{
			if (need[j + 1] == '\0')
				return ((char*)hys + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
