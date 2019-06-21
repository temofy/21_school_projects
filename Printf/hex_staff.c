/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_staff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:31:42 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/06/20 15:02:42 by aaeron-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*hexcimal(long long int *res, char *c_res, unsigned long long int tmp)
{
	int	i;

	i = 0;
	while (i < num_hex_len(tmp))
	{
		if (res[i] < 10)
			c_res[i] = (char)(res[i] + 48);
		else
			c_res[i] = (char)(res[i] + 87);
		i++;
	}
	return (c_res);
}

char	*hex_int(unsigned long long int n)
{
	int						i;
	long long int			*res;
	char					*c_res;
	unsigned long long int	tmp;
	char					*c_f_res;

	i = num_hex_len(n);
	tmp = n;
	if (n == 0 && (c_res = ft_strnew(1)))
	{
		*c_res = '0';
		return (c_res);
	}
	if (!(res = (long long int*)malloc(sizeof(long long int) * i))
		|| !(c_res = ft_strnew((size_t)i)))
		return (NULL);
	while (--i >= 0)
	{
		res[i] = n % 16;
		n = n / 16;
	}
	c_res = hexcimal(res, c_res, tmp);
	free(res);
	return (c_res);
}

char	*push_hex(va_list arg, t_formatting *e_sequence, char **hex)
{
	if (e_sequence->length_modifier == 216 ||\
	e_sequence->length_modifier == 108)
		*hex = hex_int(va_arg(arg, unsigned long long));
	else if (e_sequence->length_modifier == 106)
		*hex = hex_int(va_arg(arg, uintmax_t));
	else
		*hex = hex_int(va_arg(arg, unsigned int));
	return (*hex);
}
