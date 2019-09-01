/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 11:57:47 by cheller           #+#    #+#             */
/*   Updated: 2019/06/30 11:57:49 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str)
{
	int words;
	int flag;

	words = 0;
	flag = 0;
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str >= 33 && *str <= 126 && !flag)
		{
			flag = 1;
			words++;
		}
		else if (*str < 33 || *str > 126)
			flag = 0;
		str++;
	}
	return (words);
}
