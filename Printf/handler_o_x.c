/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_o_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:34:34 by cheller           #+#    #+#             */
/*   Updated: 2019/04/17 15:44:46 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_sizedup(const char *s, size_t n)
{
	unsigned int	i;
	char			*res;

	if ((res = (char*)malloc(sizeof(*res) * (n + 1))))
	{
		i = -1;
		while (*s && ++i < n)
			res[i] = s[i];
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}

int num_oct_len(long int n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n/8;
		i++;
	}
return (i);
}

char *oct_int(long int n)
{
	int i;
	long int *res;
	char *c_res;
	long int tmp = n;

	i = num_oct_len(n) - 1;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
	*c_res = '0';
	return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int)*num_oct_len(n))) || !(c_res = (char*)malloc(sizeof(char)*num_oct_len(n))))
	return (NULL);
	while (i >= 0)
	{
	res[i] = n%8;
	i--;
	n = n/8;
	}
	while (i < num_oct_len(tmp))
	{
	c_res[i] = (char)(res[i] + 48);
	i++;
	}
	return (c_res);
}

char *hex_int(long int n)
{
	int i;
	long int *res;
	char *c_res;
	long int tmp = n;
	char *c_f_res;

	i = num_hex_len(n) - 1;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
	*c_res = '0';
	return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int)*(num_hex_len(n)))) || !(c_res = (char*)malloc(sizeof(char)*num_hex_len(n))))
	return (NULL);
	while (i >= 0 && n/16 <= tmp)
	{
	res[i] = n%16;
	i--;
	n = n/16;
	}
	i = 0;
	while (i < num_hex_len(tmp) )
	{
	if (res[i] < 10)
		c_res[i] = (char)(res[i] + 48);
	else
		c_res[i] = (char)(res[i] + 87);
	i++;
	}
	c_f_res = ft_sizedup(c_res, num_hex_len(tmp));
	return (c_f_res);
}

char *hex_int_big(long int n)
{
	int i;
	long int *res;
	char *c_res;
	long int tmp = n;
	char *c_f_res;

	i = num_hex_len(n) - 1;
	if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
	{
	*c_res = '0';
	return (c_res);
	}
	if (!(res = (long int*)malloc(sizeof(long int)*(num_hex_len(n)))) || !(c_res = (char*)malloc(sizeof(char)*num_hex_len(n))))
	return (NULL);
	while (i >= 0 && n/16 <= tmp)
	{
	res[i] = n%16;
	i--;
	n = n/16;
	}
	i = 0;
	while (i < num_hex_len(tmp) )
	{
	if (res[i] < 10)
		c_res[i] = (char)(res[i] + 48);
	else
		c_res[i] = (char)(res[i] + 55);
	i++;
	}
	c_f_res = ft_sizedup(c_res, num_hex_len(tmp));
	return (c_f_res);
}

char	*handler_o(va_list arg, t_formatting *e_sequence)
{
	char *oct;
	
	oct = oct_int((int)va_arg(arg, void *));
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


	res = oct;
	len = ft_strlen(oct);
	if (t <= 0 && e_sequence->flags->minus == 0 && e_sequence->flags->zero == 1)
	{
		if (e_sequence->flags->hash == 1)
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
	if (e_sequence->flags->hash == 1)
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

char	*handler_x(va_list arg, t_formatting *e_sequence)
{
	char *hex;
	
	hex = hex_int((int)va_arg(arg, void *));
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


	res = hex;
	len = ft_strlen(hex);
	if (t <= 0 && e_sequence->flags->minus == 0 && e_sequence->flags->zero == 1)
	{
		if (e_sequence->flags->hash == 1)
		{
			res = ft_strjoin("0x", res);
			len+=2;
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
	if (e_sequence->flags->hash == 1)
	{
		res = ft_strjoin("0x", res);
		len+=2;
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

char	*handler_x_big(va_list arg, t_formatting *e_sequence)
{
	char *hex;
	
	hex = hex_int_big((int)va_arg(arg, void *));
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


	res = hex;
	len = ft_strlen(hex);
	if (t <= 0 && e_sequence->flags->minus == 0 && e_sequence->flags->zero == 1)
	{
		if (e_sequence->flags->hash == 1)
		{
			res = ft_strjoin("0X", res);
			len+=2;
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
		if (e_sequence->flags->hash == 1)
		{
			res = ft_strjoin("0X", res);
			len+=2;
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
			while (len < w)
			{
			res = ft_strjoin(" ", res);
			len = ft_strlen(res);
			}
	}
	e_sequence->common_length += len;
	return (res);
}