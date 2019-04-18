/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:00:01 by cheller           #+#    #+#             */
/*   Updated: 2019/04/18 16:48:49 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_sequence_f(char *nbr_str, t_formatting *e_seq, char **str)
{
	return (NULL);
}

char	*handler_f(va_list arg, t_formatting *e_seq)
{
	char	*nbr_str;
	char	*str;	

	if (e_seq->length_modifier == 108)
		nbr_str = ft_litoa(va_arg(arg, long int));
	else if (e_seq->length_modifier == 76)
		nbr_str = ft_litoa(va_arg(arg, long long int));
	if (*nbr_str == '-')
		e_seq->is_negative = 1;	
	str = handler_sequence_f(nbr_str, e_seq, &str);
	return (str);
}