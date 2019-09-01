/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:41:02 by cheller           #+#    #+#             */
/*   Updated: 2019/08/25 12:41:16 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strmatrix(int m, int n)
{
	char	**matrix;
	int		i;

	i = 0;
	if (n < 1 && m < 1)
		return (NULL);
	matrix = malloc(sizeof(char**) * (m + 1));
	while (i < m)
	{
		matrix[i] = ft_strnew(n);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
