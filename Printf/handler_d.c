/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:45:58 by cheller           #+#    #+#             */
/*   Updated: 2019/04/25 21:01:57 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_seq)
{
	int		len_arg;

	len_arg = ft_strlen(*str_arg);
	if (e_seq->flags->minus) 	// flag "-"
		ft_memset(*str, ' ', len_str);
	else if (e_seq->flags->zero && e_seq->precision == -1) 		// flag "0"
	{
		ft_memset(*str, '0', len_str);
		if (e_seq->is_negative && len_str > 0)
		{
			**str = '-';
			**str_arg = '0';
		}
		else if(!e_seq->is_negative)
			if (e_seq->flags->plus)
				**str = '+';
	}
	if (e_seq->flags->plus) 	// flag "+"
	{
		if (len_str > 0)
		{
			if (e_seq->precision >= e_seq->width)
			{
				if (e_seq->is_negative)
					*str = ft_strfjoin("-", *str, 2);
				else 
					*str = ft_strfjoin("+", *str, 2);
			}
			else if (e_seq->precision > len_arg - 1)
			{
				if (e_seq->is_negative)
				{
					**str_arg = '0';
					*(*str + ((len_str + len_arg) - e_seq->precision - 1)) = '-';
				}
				else
					*(*str + ((len_str + len_arg) - e_seq->precision - 1)) = '+';
			}
			else if (e_seq->precision >= 0)
			{
				if (!e_seq->is_negative && e_seq->precision <= len_arg)
				{
					*str_arg = ft_strfjoin ("+", *str_arg, 2);
					*(*str + (len_str - 1)) = '\0';
				}
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
	length_arg = ft_strlen(*str_arg);
	length_str = handler_length(length_arg, width, precision);
	*str = ft_strnew(length_str);
	if (length_str > 0 && precision >= width)
		ft_memset(*str, '0', length_str);
	else if (length_str > 0 && width > precision && precision > length_arg)
	{
		ft_memset(*str, ' ', length_str);
		ft_memset(*str + (width - precision), '0', precision - length_arg);	
	}
	else if (length_str > 0)
		ft_memset(*str, ' ', length_str);
	if (e_sequence->is_negative && e_sequence->precision > length_arg)
	{
		**str_arg = '0';
		if (width > precision)		
			*(*str + ((length_str + length_arg) - e_sequence->precision - 1)) = '-';
		else if (width <= precision && !e_sequence->flags->plus)
			*str = ft_strfjoin("-", *str, 2);
	}	
	if (count_amount_flags(e_sequence) > 0)
		return(*str = handler_d_flags(&*str, &*str_arg, length_str, e_sequence));
	*str = ft_strfjoin(*str, *str_arg, 0);
	return (*str);
}

/*char	*handler_d_flags(char **str, char *str_arg, int len_str, t_formatting *e_seq)
{
	int		len_arg;
	int		prec;
	int		width;
	
	len_arg = ft_strlen(str_arg);
	if (e_seq->flags->minus) 	// flag "-"
		ft_memset(*str, ' ', len_str);
	else if (e_seq->flags->zero && e_seq->precision == -1) 		// flag "0"
	{
		ft_memset(*str, '0', len_str);
		if (e_seq->is_negative && len_str > 0)
			**str = '-';
	}*/
	/*else if (e_seq->flags->zero && e_seq->precision >= len_arg && e_seq->flags->plus == 0) // оптимизировать и унифицировать прибавление -
	{
		if (e_seq->is_negative && e_seq->precision < e_seq->width)
			**str = '-';
		else
		{
			*str = ft_strfjoin("-", *str, 2);
			e_seq->common_length++;
		}
		e_seq->common_length++;	
		
	}*/
	/*else if (e_seq->flags->zero && !e_seq->flags->plus && e_seq->is_negative ) // ужасно, исправить!!!
	{
		if (e_seq->precision >= e_seq->width)
		{
			*str = ft_strfjoin("-", *str, 2);
			e_seq->common_length++;
		}
		else if (len_arg > 0)		
			**str = '-';
	}
	if (e_seq->flags->plus) 	// flag "+"
	{
		if (len_str > 0)
		{
			if (e_seq->precision >= e_seq->width)
			{
				if (e_seq->is_negative)
					*str = ft_strfjoin("-", *str, 2);
				else 
					*str = ft_strfjoin("+", *str, 2);
				e_seq->common_length++;
			}
			else if (e_seq->precision > len_arg)
			{
				if (e_seq->is_negative)
				{
					//str_arg = '0';
					*(*str + ((len_str + len_arg) - e_seq->precision - 1)) = '-';
				}
				else
					*(*str + ((len_str + len_arg) - e_seq->precision - 1)) = '+';
			}
			else if (e_seq->precision >= 0)
			{
				if (!e_seq->is_negative && e_seq->precision <= len_arg)
				{
					str_arg = ft_strfjoin ("+", str_arg, 2);
					*(*str + (len_str - 1)) = '\0';
				}
				else if (e_seq->is_negative && e_seq->precision <= len_arg)
				{
					str_arg = ft_strfjoin ("-", str_arg, 2);
					*(*str + (len_str - 1)) = '\0';
				}
			}
		}
		else
			if (!e_seq->is_negative)
				*str = ft_strfjoin(*str, "+", 1);
	}
	if (e_seq->flags->space && !e_seq->flags->plus && !e_seq->flags->minus && !e_seq->is_negative) 	// flag " "
		**str = ' ';
	if (e_seq->flags->minus)
		*str = ft_strjoin(str_arg, *str);
	else		
		*str = ft_strjoin(*str, str_arg); //утечка
	return (*str);
}

char	*handler_sequence_d(char *str_arg, t_formatting *e_seq, char **str)
{
	int		length_arg;
	int		length_str;
	int		width;
	int		precision;

	width = e_seq->width;
	precision = e_seq->precision;
	length_arg = ft_strlen(str_arg);	//arguments's length with sign
	length_str = handler_length(length_arg, width, precision); //counting remaining length
	*str = ft_strnew(length_str);
	e_seq->common_length += length_str + length_arg;
	if (length_str > 0 && precision >= width)
		ft_memset(*str, '0', length_str);
	else if (length_str > 0 && width > precision && precision > length_arg)
	{
		ft_memset(*str, ' ', length_str);
		ft_memset(*str + (width - precision), '0', precision - length_arg);	
	}
	else if (length_str > 0)
		ft_memset(*str, ' ', length_str);
	if (count_amount_flags(e_seq) > 0)
		return(*str = handler_d_flags(&*str, str_arg, length_str, e_seq));
	char *str1 = *str + 1;
	if (e_seq->is_negative && e_seq->precision > length_arg)
	{
		if (width > precision)		
			*(*str + ((length_str + length_arg) - e_seq->precision - 1)) = '-';
		else if (width <= precision && !e_seq->flags->plus)
			*str = ft_strfjoin("-", *str, 2);
	}
	if (e_seq->is_negative)
	{
		if (precision >= width)
			e_seq->common_length++;*/
		/*if (precision <= length_arg)
		{
			str_arg--;
			*str = ft_strfjoin(*str, str_arg, 2);
		}
		else
		{*/
			//*str = ft_strfjoin(*str, str_arg, 2);
			//free(--str_arg);
		//}		
	//}
	/*else
		*str = ft_strfjoin(*str, str_arg, 0);
	return (*str);
}*/

char	*handler_d(va_list arg, t_formatting *e_seq)
{
	char	*nbr_str;
	char	*str;

	if (e_seq->length_modifier == 108)
		nbr_str = ft_litoa(va_arg(arg, long int));
	else if (e_seq->length_modifier == 216)
		nbr_str = ft_litoa(va_arg(arg, long long int));
	else if (e_seq->length_modifier == 104)
		nbr_str = ft_itoa((short int)va_arg(arg, int));
	else if (e_seq->length_modifier == 208)
		nbr_str = ft_itoa((signed char)va_arg(arg, int));
	else if (e_seq->length_modifier == 106)
		nbr_str = ft_itoa((signed char)va_arg(arg, int));
	else if (e_seq->length_modifier == 122)
		nbr_str = ft_ulitoa(va_arg(arg, size_t));
	else
		nbr_str = ft_itoa(va_arg(arg, int)); // для разных флагов
	if (*nbr_str == '-')
	{
		//nbr_str++;
		e_seq->is_negative = 1;
	}
	str = handler_sequence_d(&nbr_str, e_seq, &str);
	e_seq->common_length = ft_strlen(str);
	return (str);
}