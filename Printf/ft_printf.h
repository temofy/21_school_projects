/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:23:51 by cheller           #+#    #+#             */
/*   Updated: 2019/04/25 19:19:37 by cheller          ###   ########.fr       */
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
}						t_flags;

typedef struct	s_formatting
{
	t_flags	*flags;
	int		is_negative;
	int		width;
	int		precision;
	int		length_modifier;
	char	specifier;
	int		common_length;
}						t_formatting;

/*struct		bigint 
{
	char sign;
	char *exp[16];
	char int_part;
	char *frac[64];
};*/

typedef union d_l
{	
	long double ld;
	unsigned char b[16];
} t_dl;

typedef struct	floating_point
{
	char sign;
	char *exp;
	char int_part;
	char *frac;
	char *binary_represent;
	t_dl *binary;
}		t_fp;

struct	bignum
{
	char	**integer;
	char	**frac;
};

typedef struct	str_fp
{
	char	*integer;
	char	*frac;
	struct 	bignum *dec_represent;
}	t_str_fp;


int		ft_printf(const char *format, ...);
int		find_end_spec(char chr);
t_flags	*check_flags(const char *format);
int		check_sign(const char *format);
int		check_width(const char *format);
int		check_precision(const char *format);
int		check_length_modifier(const char *format);
char	check_spec(const char *string);
void	print_sequence(t_formatting *e_sequence);
int		count_amount_flags(t_formatting *e_seq);
int		handler_length(int length, int width, int precision);
/* handler_d */
char	*handler_d_flags(char **str, char **str_arg, int len_str, t_formatting *e_seq);
char	*handler_sequence_d(char **str_arg, t_formatting *e_sequence, char **str);
char	*handler_d(va_list arg, t_formatting *e_sequence);
/* handler_d */
char	*handler_u(va_list arg, t_formatting *e_sequence);
char	*handler_f(va_list arg, t_formatting *e_sequence);
char	*handler_sequence_f(char *nbr_str, t_formatting *e_seq, char **str);

char	*handler_x(va_list arg, t_formatting *e_sequence);
char	*handler_o(va_list arg, t_formatting *e_sequence);
char	*handler_x_big(va_list arg, t_formatting *e_sequence);
/* hex.c */
char 	*hex_long_int(long int n);
int 	num_hex_len(long int n);

/* handler_text */
char	*handler_s(va_list arg, t_formatting *e_sequence);
char	*handler_c(va_list arg, t_formatting *e_sequence);
/* handler_p */
char	*handler_p(va_list arg, t_formatting *e_sequence);
#endif
