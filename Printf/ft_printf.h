/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:23:51 by cheller           #+#    #+#             */
/*   Updated: 2019/05/22 16:23:38 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "libft/libft.h"

typedef struct	s_flags
{
	int		space;
	int		plus;
	int		minus;
	int		hash;
	int		zero;
}				t_flags;

typedef struct	s_formatting
{
	t_flags	*flags;
	int		is_negative;
	int		width;
	int		precision;
	int		length_modifier;
	char	specifier;
	int		common_length;
}				t_formatting;

typedef union       ld_nbr
{	
	long double     ld;
	unsigned char   b[16];
}                   t_ld_nbr;

typedef struct		floating_point
{
	char        sign;
	char        *exp;
	char        int_part;
	char        *frac;
	char        *binary_represent;
	t_ld_nbr    *binary;
}		        	t_float;

typedef struct		long_value
{
	int		*values;
	int		length;
}					t_long_value;


typedef struct	str_fp
{
	char	*integer;
	char	*frac;
}				t_str_fp;

int				ft_printf(const char *format, ...);
int				find_end_spec(char chr);
t_flags			*check_flags(const char *format);
int				check_width(const char *format);
int				check_precision(const char *format);
int				check_length_modifier(const char *format);
char			check_spec(const char *string);
int				count_amount_flags(t_formatting *e_seq);
int				handler_length(int length, int width, int precision);

char			*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_seq);
char			*handler_sequence_d(char **str_arg, t_formatting *e_sequence, char **str);
char			*handler_d(va_list arg, t_formatting *e_sequence);

char			*handler_u(va_list arg, t_formatting *e_sequence);
char			*handler_f(va_list arg, t_formatting *e_sequence);
char			*handler_sequence_f(char *str, t_formatting *e_seq, t_str_fp *str_fp);

char 			*handler_x(va_list arg, t_formatting *e_sequence);
char			*handler_o(va_list arg, t_formatting *e_sequence);
char 			*handler_x_big(va_list arg, t_formatting *e_sequence);

char			*hex_long_int(long int n);
int				num_hex_len(long int n);

char			*handler_s(va_list arg, t_formatting *e_sequence);
char			*handler_c(va_list arg, t_formatting *e_sequence);
char			*handler_b(va_list arg, t_formatting *e_sequence);

char			*handler_p(va_list arg, t_formatting *e_sequence);

t_float			*fill_fp(long double ldbl);
char			*represent_binary(unsigned char *bytes);
char			*present_int_as_bin(unsigned char number);
unsigned long	bin_as_dec(char *bin);
void			free_str_fp(t_str_fp **str_fp);
void			free_fp(t_float **fp);
char			*get_number(t_float *fp, t_formatting *e_seq);
char			*handler_ambiguity(t_float *fp, char *str, t_formatting *e_seq);

t_long_value	la_pow(t_long_value nbr, int exp);
t_long_value	conv_to_la(signed long nbr);
t_long_value 	karatsuba_mul(t_long_value a, t_long_value b);
t_long_value	normalize(t_long_value l);
t_long_value	sum(t_long_value a, t_long_value b);
char			*conv_bignum_to_str(t_long_value nbr);

#endif
