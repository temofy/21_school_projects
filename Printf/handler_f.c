/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:00:01 by cheller           #+#    #+#             */
/*   Updated: 2019/05/20 20:17:27 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handler_flags_f(char **str, t_formatting *e_seq, char **spaces)
{
	if (e_seq->flags->minus)
		*str = ft_strfjoin(*str, *spaces, 0);
	else if (e_seq->flags->zero)
		*str = ft_strfjoin(*spaces, *str, 0);
	if (e_seq->is_negative)
		*str = ft_strfjoin("-", *str, 2);
	else if (e_seq->flags->plus)
		*str = ft_strfjoin("+", *str, 2);
	if (!e_seq->flags->minus && !e_seq->flags->zero)
		*str = ft_strfjoin(*spaces, *str, 0);
}

char	*handler_s_f(char **s, t_formatting *e_seq, t_str_fp *s_fp, char **sps)
{
	int		length;

	*sps = ft_strnew(0);
	round_frac(&s_fp, e_seq->precision);
	if (e_seq->precision != 0)
	{
		*s = ft_strjoin(s_fp->integer, ".");
		*s = ft_strfjoin(*s, s_fp->frac, 1);
	}
	else
		*s = ft_strdup(s_fp->integer);
	length = ft_strlen(*s);
	e_seq->width -= e_seq->is_negative;
	if (!e_seq->is_negative)
		e_seq->width -= e_seq->flags->plus;
	if (e_seq->width > length)
	{
		*sps = ft_strfjoin(*sps, ft_strnew_set(' ', e_seq->width - length), 0);
		if (e_seq->flags->zero && !e_seq->flags->minus)
			ft_memset(*sps, '0', e_seq->width - length);
		else
			ft_memset(*sps, ' ', e_seq->width - length);
	}
	handler_flags_f(&*s, e_seq, &*sps);
	return (*s);
}

char	*handler_ambiguity(t_float *fp, char **s, t_formatting *e_s, char **sps)
{
	int		is_inf;
	int		i;
	int		width;

	i = -1;
	is_inf = 1;
	while (++i < 64)
		if (fp->frac[i] == '1')
			is_inf = 0;
	if (is_inf)
		*s = ft_strdup("inf");
	else
		*s = ft_strdup("nan");
	if (is_inf && e_s->is_negative)
		*s = ft_strfjoin("-", *s, 2);
	if (is_inf && e_s->flags->plus && !e_s->is_negative)
		*s = ft_strfjoin("+", *s, 2);
	width = e_s->width - ft_strlen(*s);
	*sps = ft_strnew(width);
	*sps = ft_memset(*sps, ' ', width);
	if (e_s->flags->minus)
		*s = ft_strfjoin(*s, *sps, 0);
	else
		*s = ft_strfjoin(*sps, *s, 0);
	return (*s);
}

t_float	*fill_fp(long double ldbl)
{
	t_float	*fp;

	if (!(fp = (t_float*)malloc(sizeof(t_float))))
		return (NULL);
	fp->binary = (t_ld_nbr*)malloc(sizeof(t_ld_nbr));
	fp->binary->ld = ldbl;
	fp->binary_represent = represent_binary(fp->binary->b, 10);
	fp->sign = *fp->binary_represent;
	fp->exp = ft_strsub(fp->binary_represent, 1, 15);
	fp->int_part = *(fp->binary_represent + 16);
	fp->frac = ft_strsub(fp->binary_represent, 17, 63);
	return (fp);
}

char	*handler_f(va_list arg, t_formatting *e_seq)
{
	char			*str;
	t_float			*fp;
	long double		ld;
	char			*spaces;

	if (e_seq->length_modifier == 76)
		ld = (long double)va_arg(arg, long double);
	else
		ld = (long double)va_arg(arg, double);
	fp = fill_fp(ld);
	e_seq->is_negative = fp->sign - '0';
	get_nbr(fp, e_seq, &str, &spaces);
	free_fp(&fp);
	e_seq->common_length = ft_strlen(str);
	return (str);
}
