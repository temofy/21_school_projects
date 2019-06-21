/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oct_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:32:57 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 15:07:41 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*oct_total_hh(char n)
{
	char *oct;

	if (n < 0)
	{
		oct = oct_int(256 + (char)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}

char	*oct_total_h(short int n)
{
	char *oct;

	if (n < 0)
	{
		oct = oct_int(65536 + (short int)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}

char	*oct_total(int n, t_formatting *e_sequence)
{
	char	*oct;

	if (e_sequence->length_modifier == 104)
	{
		oct = oct_total_h((short int)n);
		return (oct);
	}
	if (e_sequence->length_modifier == 208)
	{
		oct = oct_total_hh((char)n);
		return (oct);
	}
	if (n < 0)
	{
		oct = oct_int(4294967296 + (int)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}

char	*oct_total_l(long int n)
{
	char	*oct;

	if (n < 0)
	{
		oct = oct_int(4294967296 + (long int)n);
		return (oct);
	}
	else
	{
		oct = oct_int((long)ft_abs(n));
		return (oct);
	}
}
