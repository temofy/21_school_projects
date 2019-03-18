/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:45:58 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 19:26:56 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char	*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_seq)
{
	if (e_seq->flags->minus) 	// flag "-"
		ft_memset(*str, ' ', len_str);
	else if (e_seq->flags->zero) 		// flag "0"
	{
		ft_memset(*str, '0', len_str);
		if (e_seq->is_negative && len_str > 0)
		{
			**str = '-';
			**str_arg = '0';
		}
	}
	if (e_seq->flags->plus) 	// flag "+"
	{
		if (len_str > 0)
		{
			if (e_seq->flags->zero)
			{
				if (!e_seq->is_negative)
					**str = '+';
			}
			else		
				if (!e_seq->is_negative)
				{
					*str_arg = ft_strjoin ("+", *str_arg);
					*(*str + (len_str - 1)) = '\0';
				}
		}
		else
			if (!e_seq->is_negative)
				*str = ft_strfjoin(*str, "+", 1);
	}
	if (e_seq->flags->space && !e_seq->flags->plus && !e_seq->flags->minus && !e_seq->is_negative) 	// flag " "
		**str = ' ';
	else if (e_seq->flags->space && e_seq->flags->minus && !e_seq->flags->plus)
	{
		*str_arg = ft_strfjoin(" ", *str_arg, 2);
		*(*str + len_str - 1) = '\0';
	}
	if (e_seq->flags->minus)
		*str = ft_strjoin(*str_arg, *str);
	else		
		*str = ft_strjoin(*str, *str_arg); //утечка
	return (*str);
}

char	*handler_sequence_d(char **str_arg, t_formatting *e_sequence, char **str)
{
	int		length_arg;
	int		length_str;
	int		width;
	int		precision;

	width = e_sequence->width;
	precision = e_sequence->precision;
	length_arg = ft_strlen(*str_arg);	//arguments's length with sign
	length_str = handler_length(length_arg, width, precision); //counting remaining length
	printf("length: %d\n", length_str);
	//print_sequence(e_sequence);
	*str = ft_strnew(length_str);
	ft_memset(*str, ' ', length_str); 
	if (count_amount_flags(e_sequence) > 0)
		return(*str = handler_d_flags(&*str, &*str_arg, length_str, e_sequence));
	else if (length_str > 0 && precision >= width)
		ft_memset(*str, '0', length_str);
	else if (length_str > 0 && width > precision && precision > length_arg)
	{
		ft_memset(*str, ' ', length_str);
		ft_memset(*str + (width - precision), '0', precision - length_arg);
	}
	else if (length_str > 0)
		ft_memset(*str, ' ', length_str);
	*str = ft_strjoin(*str, *str_arg); //утечка
	return (*str);
}

char	*handler_d(va_list arg, t_formatting *e_sequence)
{
	char	*nbr_str;
	char	*str;	
	int		length;

	if (e_sequence->length_modifier == 108)
		nbr_str = ft_litoa(va_arg(arg, long int));
	else
		nbr_str = ft_itoa(va_arg(arg, int)); // для разных флагов
	if (*nbr_str == '-')
		e_sequence->is_negative = 1;
	str = handler_sequence_d(&nbr_str, e_sequence, &str);
	return (str);
}