/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:00:01 by cheller           #+#    #+#             */
/*   Updated: 2019/04/23 17:54:29 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char	*PresentIntAsBin(unsigned char number)
{
    char	*bin;
    int		i;

    i = 8;
    bin = ft_strnew(8);
    while (i--)
    {
        *bin = ((number >> i) & 1) + '0';
        bin++;
    }
    return (bin - 8);
}

char	*Represent_binary(unsigned char *bytes)
{
    char    *binary;
    int     i;
    int     j;

    i = 0;
    j = 9;
    if (!(binary = ft_strnew(80)))
        return (NULL);
    while (i++ < 10)
        binary = ft_strfjoin(binary, PresentIntAsBin(bytes[j--]), 0);
    return (binary);
}

unsigned long	BinAsDec(char *bin)
{
    unsigned long	decimal;
    unsigned long	factor;
    size_t	len;

    factor = 1;
    len = ft_strlen(bin);
    decimal = 0;
    while (len--)
    {
        if (bin[len] == '1')
        {
            decimal += 1 * factor;
        }
        factor *= 2;
    }
    return (decimal);
}

char	*GetDecimalIntStr(char *bin)
{
    char    *str;

    str =  ft_ulitoa((unsigned long long)BinAsDec(bin));
    free(bin);
    bin = NULL;
    return (str);
}

t_str_fp	*GetDecimalFracStr(char *frac_bin, t_str_fp *str)
{
    int		i;
    int		k;
    size_t	len;
    t_long_value	tmp;
    t_long_value	result;

    result.values = (int*)malloc(sizeof(int) * 1);
    result.values[0] = 0;
    result.length = 0;
    i = 0;
    len = ft_strlen(frac_bin);
    while (i < len)
    {
        if (frac_bin[i] == '1')
        {
            tmp = karatsuba_mul((ft_la_pow(conv_to_la(5) , i + 1)), ft_la_pow(conv_to_la(10), len - i - 1)); // pow
            result = sum(result, tmp);
            free(tmp.values);
        }
        i++;
    }
    free(str->frac);
    str->frac = ConvBigNumToStr(result);
    //printf("string: %s\n", str->frac);
    return (str);
}

char    *GetLeadingZeros(int amount)
{
    char    *leading_zeros;

    leading_zeros = strdup("");
    if (amount == 0)
        return (leading_zeros);
    while (amount--)
        leading_zeros = ft_strfjoin("0", leading_zeros, 2);
    return (leading_zeros);
}
char    *GetFracZeros(long double nbr)
{
    int     zeros;
    int     integer;
    char    *StrZeros;

    integer = nbr;
    if (integer)
        return(ft_strdup(""));
    zeros = 0;
    while (!integer)
    {
        nbr = nbr * 10;
        integer = (int)nbr;
        zeros++;
    }
    zeros--;
    StrZeros = ft_strnew(zeros);
    StrZeros = ft_memset(StrZeros, 48, zeros);
    return (StrZeros);
}

char    *RoundFracPart(char *decimal_frac, int precsion)
{
    return (NULL);
}

char	*handler_sequence_f(char *str, t_formatting *e_seq, t_str_fp *str_fp)
{

    return (NULL);
}

char	*Get_Number(t_float *fp, t_formatting *e_seq)
{
    long double		dec_number;
    unsigned long	dec_mantissa;
    int				exp;
    t_str_fp		*str_fp;
    char            *str;

    str_fp = (t_str_fp*)malloc(sizeof(t_str_fp));
    exp = (BinAsDec(fp->exp) - 16383); // заменить
    //printf("exp_binary: %s\nexp: %i\n", fp->exp, exp);
    if (exp >= 0) {
        str_fp->integer = ft_strdup(&fp->int_part);
        str_fp->integer = ft_strjoin(str_fp->integer, ft_strsub(fp->frac, 0, exp));
        str_fp->frac = ft_strsub(fp->frac, exp, 63 - exp);
        //printf("int: %s\nfrac: %s\n", str_fp->integer, str_fp->frac);
        //printf("decimal integer part: %lu\n", BinAsDec(str_fp->integer));
        dec_number = pow(2, exp);
        dec_number *= (1 + (dec_mantissa / pow(2, 63)));
    }
    else{
        str_fp->integer = ft_strdup("0");
        str_fp->frac = ft_strjoin(&fp->int_part, fp->frac);
        str_fp->frac = ft_strjoin(GetLeadingZeros(abs(exp + 1)), str_fp->frac);
        //printf("int: %s\nfrac: %s\n", str_fp->integer, str_fp->frac);
    }
    str_fp = GetDecimalFracStr(str_fp->frac, str_fp);
    str_fp->integer = GetDecimalIntStr(str_fp->integer);
    str_fp->frac = ft_strfjoin(GetFracZeros(fp->binary->ld), str_fp->frac, 0);
    str = ft_strfjoin(str_fp->integer, ".", 1);
    handler_sequence_f(str, e_seq, str_fp);
    str = ft_strfjoin(str, str_fp->frac, 0);
    return (str);
}

t_float	*Fill_FP(long double Ldbl)
{
    t_float     *float_point;

    if (!(float_point = (t_float*)malloc(sizeof(t_float))))
        return (NULL);
    float_point->binary = (t_ld_nbr*)malloc(sizeof(t_ld_nbr));
    float_point->binary->ld = Ldbl;
    float_point->binary_represent = Represent_binary(float_point->binary->b);
    float_point->sign = *float_point->binary_represent;
    float_point->exp = ft_strsub(float_point->binary_represent, 1, 15);
    float_point->int_part = *(float_point->binary_represent + 16);
    float_point->frac = ft_strsub(float_point->binary_represent, 17, 63);
    return (float_point);
}

char	*handler_f(va_list arg, t_formatting *e_seq)
{
	char	*nbr_str;
	char   	*str;
    t_float *fp;
    long double     ld;


	if (e_seq->length_modifier == 76)
	    ld = (long double)va_arg(arg, long double);
	else
	    ld = (double)va_arg(arg, double);
	fp = Fill_FP(ld);
	e_seq->is_negative = fp->sign - '0';
	str = Get_Number(fp, e_seq);
	printf("my printf %s\n", str);
	return (str);
}