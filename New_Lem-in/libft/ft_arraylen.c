/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 13:11:04 by cheller           #+#    #+#             */
/*   Updated: 2019/06/20 13:11:35 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_arraylen(void **array)
{
	int	len;

	if (!array)
		return (-1);
	len = 0;
	while (*array != NULL)
	{
		array++;
		len++;
	}
	return (len);
}
