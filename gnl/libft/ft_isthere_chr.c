/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isthere_chr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:47:25 by cheller           #+#    #+#             */
/*   Updated: 2019/02/07 13:37:55 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isthere_chr(char *s, int c)
{
	int	is_chr;
	int	i;

	if(!s)
		return (-1);
	i = -1;
	is_chr = 0;
	while (s[++i] != '\0')
		if (s[i] == (char)c)
			is_chr = 1;
	return (is_chr);
}
