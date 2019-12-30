/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:31:09 by cheller           #+#    #+#             */
/*   Updated: 2019/06/26 14:31:15 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(char ***arr)
{
	char	**tmp;

	if (!arr)
		return ;
	tmp = *arr;
	if (arr && *arr)
	{
		while (**arr)
		{
			free(**arr);
			(*arr)++;
		}
		free(tmp);
	}
	*arr = NULL;
}
