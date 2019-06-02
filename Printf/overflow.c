/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:15:55 by cheller           #+#    #+#             */
/*   Updated: 2019/06/01 14:16:26 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		overflow_frac(t_str_fp **fp, char *nbr, int pos)
{
	int		carry;

	carry = 0;
	if (pos == -1)
		return (for_round_int(&*fp, nbr));
	while (pos >= 0)
	{
		if (nbr[pos] == '9')
		{
			nbr[pos] = '0';
			carry = 1;
			pos--;
		}
		else if (carry > 0)
		{
			nbr[pos] += 1;
			return (0);
		}
		else
			return (0);
	}
	return (carry);
}

void	overflow_int(t_str_fp **fp, int carry)
{
	int pos;

	pos = ft_strlen((*fp)->integer) - 1;
	if (carry)
	{
		while (pos >= 0)
		{
			if ((*fp)->integer[pos] == '9')
			{
				(*fp)->integer[pos] = '0';
				carry = 1;
				pos--;
			}
			else if (carry > 0)
			{
				(*fp)->integer[pos] += 1;
				return ;
			}
		}
	}
	if (carry)
		(*fp)->integer = ft_strfjoin("1", (*fp)->integer, 2);
}

void	overflow_digit(t_str_fp **fp, int precision)
{
	int	carry;

	carry = overflow_frac(&*fp, (*fp)->frac, precision - 1);
	overflow_int(&*fp, carry);
}
