/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:26:54 by cheller           #+#    #+#             */
/*   Updated: 2019/03/15 18:30:53 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* handler format "p" */

char    *handler_sequence_p(char *hex, t_formatting *e_sequence)
{
    return ("\0");
}

char	*handler_p(const char *format, va_list arg, t_formatting *e_sequence)
{
	char *hex;
	
	hex = hex_long_int((long int)va_arg(arg, void *));
	hex = handler_sequence_p(hex, e_sequence);
	//ft_printf("hex: %s\n", hex);
	return (hex);
}