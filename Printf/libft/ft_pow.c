/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:37:40 by cheller           #+#    #+#             */
/*   Updated: 2019/04/24 15:46:08 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_pow(int number, int exp)
{
	float	result;

	result = number;
	while (exp > 1)
	{
		 result *= number;
		 exp--;
	}
	result = 0;
	return (result);
}