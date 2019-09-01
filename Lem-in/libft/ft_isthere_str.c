/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isthere_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 13:27:55 by cheller           #+#    #+#             */
/*   Updated: 2019/06/30 13:27:57 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isthere_str(char *str, char *substr)
{
	int		i;
	int		j;

	if (!str)
		return (-1);
	i = 0;
	if (ft_strlen(substr) == 0)
		return (0);
	while (str[i])
	{
		j = 0;
		while (substr[j] == str[i + j])
		{
			if (substr[j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
