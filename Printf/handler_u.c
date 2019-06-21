/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:19:58 by cheller           #+#    #+#             */
/*   Updated: 2019/04/25 19:20:43 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_u(va_list arg, t_formatting *e_sequence)
{
	char	*nbr_str;
	char	*str;

	if (e_sequence->length_modifier == 108)
		nbr_str = ft_ulitoa(va_arg(arg, unsigned long int));
	else if (e_sequence->length_modifier == 216)
		nbr_str = ft_ulitoa(va_arg(arg, unsigned long long int));
	else if (e_sequence->length_modifier == 104)
		nbr_str = ft_uitoa((unsigned short int)va_arg(arg, int));
	else if (e_sequence->length_modifier == 208)
		nbr_str = ft_uitoa((unsigned char)va_arg(arg, int));
	else if (e_sequence->length_modifier == 106)
		nbr_str = ft_ulitoa((uintmax_t)va_arg(arg, uintmax_t));
	else
		nbr_str = ft_uitoa(va_arg(arg, unsigned int));
	e_sequence->flags->space = 0;
	e_sequence->flags->plus = 0;
	nbr_str = handler_sequence_d(&nbr_str, e_sequence, str);
	return (nbr_str);
}

char	*handler_big_u(va_list arg, t_formatting *e_sequence)
{
	char	*nbr_str;
	char	*str;

	nbr_str = ft_ulitoa(va_arg(arg, unsigned long));
	e_sequence->flags->space = 0;
	e_sequence->flags->plus = 0;
	nbr_str = handler_sequence_d(&nbr_str, e_sequence, str);
	return (nbr_str);
}
