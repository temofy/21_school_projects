/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:39:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/04/30 14:39:51 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int num_bin_len(long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n/2;
		i++;
	}
return (i);
}

char *bin_int(long int n)
{
	int i;
	long int *res;
	char *c_res;
	long int tmp = n;

	i = num_bin_len(n) - 1;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
	*c_res = '0';
	return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int)*num_bin_len(n))) || !(c_res = (char*)malloc(sizeof(char)*num_bin_len(n))))
	return (NULL);
	while (i >= 0)
	{
	res[i] = n%2;
	i--;
	n = n/2;
	}
	while (i < num_bin_len(tmp))
	{
	c_res[i] = (char)(res[i] + 48);
	i++;
	}
	return (c_res);
}


char *bin_total(int n)
{
	char *bin;
	 if(n < 0)
	{
		bin = bin_int(4294967296 + (int)n);
		return (bin);
	}
	else
	{
		bin = bin_int((long)ft_abs(n));
		return (bin);
	}
	
}

char *bin_total_l(long int n)
{
	char *bin;
	 if(n < 0)
	{
		bin = bin_int(4294967296 + (long int)n);
		return (bin);
	}
	else
	{
		bin = bin_int((long)ft_abs(n));
		return (bin);
	}
	
}

char	*handler_b(va_list arg, t_formatting *e_sequence)
{
	char *bin;
	
	if (e_sequence->length_modifier == 106 || e_sequence->length_modifier == 108 || e_sequence->length_modifier == 216)
		bin = bin_total_l((long int)va_arg(arg, void *));
	else
		bin = bin_total((int)va_arg(arg, void *));
	//hex = handler_sequence_p(hex, e_sequence);

	//	long long int b;
	//b = (long long int)n;
	/*char *str;
	char *hex;
	hex = hex_long_int(b);*/
	int t = e_sequence->precision;
	int w = e_sequence->width;
	char *res;
	int len;

	if (ft_strequ(bin, "0") && t == 0)
	{
		len = 0;
		if (e_sequence->flags->minus && e_sequence->flags->hash)
		{
			res = ft_strdup("0");
			len++;
		}
		else if(e_sequence->flags->hash == 1)
		{
			len++;
			res = ft_strdup("0");
		}
		else
			res = ft_strdup(" ");
		while (len < w)
		{
		res = ft_strjoin(res, " ");	
		len++;
		}
		if(e_sequence->flags->hash == 1)
			res = ft_strjoin(res, "0");
	e_sequence->common_length += len;
	return (res);
	}
	res = bin;
	len = ft_strlen(bin);
	if (t <= 0 && e_sequence->flags->minus == 0 && e_sequence->flags->zero == 1)
	{
		if (e_sequence->flags->hash == 1 && !ft_strequ(bin, "0"))
		{
			res = ft_strjoin("0", res);
			len++;
		}
		while (len < w)
		{
			res = ft_strjoin("0", res);
			len = ft_strlen(res);
		}
	}
	else
	{
	while (len < t)
	{
	res = ft_strjoin("0", res);
	len = ft_strlen(res);
	}
	if (e_sequence->flags->hash == 1 && !ft_strequ(bin, "0")) 
	{
		res = ft_strjoin("0", res);
		len++;
	}
	if (e_sequence->flags->minus == 1)
	{
		while (len < w)
		{
		res = ft_strjoin(res, " ");
		len = ft_strlen(res);
		}
	}
	else 
	{
		while (len < w)
		{
			res = ft_strjoin(" ", res);
			len = ft_strlen(res);
		}
	}
	}
	e_sequence->common_length += len;
	return (res);
}
