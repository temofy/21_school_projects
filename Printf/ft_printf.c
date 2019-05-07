/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:49:48 by aaeron-g          #+#    #+#             */
/*   Updated: 2019/05/07 13:24:49 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <math.h>

#define PIB(x) PresentIntAsBin(x)

void	print_sequence(t_formatting *e_sequence)
{
	printf("*************-escape-sequence-*************\n");
	printf("flags: \n\tspace: %d\n", e_sequence->flags->space);
	printf("\tplus: %d\n", e_sequence->flags->plus);
	printf("\tminus: %d\n", e_sequence->flags->minus);
	printf("\thash: %d\n", e_sequence->flags->hash);
	printf("\tzero: %d\n", e_sequence->flags->zero);
	printf("width: %d\n", e_sequence->width);
	printf("precision: %d\n", e_sequence->precision);
	printf("negative: %d\n", e_sequence->is_negative);
	printf("length_modifier: %d\n", e_sequence->length_modifier);
	printf("********************************************\n");
}

int		handler_length(int length, int width, int precision)
{
	if (length > width && length > precision)
		return (0);
	else if (length < width && length >= precision)
		return (width - length);
	else if (length >= width && length < precision)
		return (precision - length);
	else if (length < width && length < precision)
	{
		if (width > precision)
			return (width - length);
		else
			return (precision - length);
	}
	return (0);
}

int		count_amount_flags(t_formatting *e_seq)
{
	int		amount;

	amount = 0;
	amount += e_seq->flags->space;
	amount += e_seq->flags->plus;
	amount += e_seq->flags->minus;
	amount += e_seq->flags->hash;
	amount += e_seq->flags->zero;
	return (amount);
}

t_formatting	*scanning_sequence(const char *format)
{
	t_formatting	*e_sequence;

	if (!(e_sequence = (t_formatting*)malloc(sizeof(t_formatting))))
		return (NULL);
	e_sequence->flags = check_flags(format);
	e_sequence->width = check_width(format);
	e_sequence->precision = check_precision(format);
	e_sequence->length_modifier = check_length_modifier(format);
	e_sequence->specifier = check_spec(format);
	e_sequence->common_length = 0; // везде записывать
	return (e_sequence);
}

char	*handler_percent(t_formatting *e_seq)
{
	char	*str;
	int		str_len;

	str_len = handler_length(1, e_seq->width, 0);
	str = ft_strnew(str_len);
	ft_memset(str, ' ', str_len);
	e_seq->common_length += str_len + 1;
	if (e_seq->flags->minus)
		str = ft_strfjoin("%", str, 2);
	else
		str = ft_strfjoin(str, "%", 1);
	return (str);
}

char	*find_specifier(const char *format, va_list arg, t_formatting *e_sequence)
{
	int		i;
	
	i = 0;
	while (format[i++])
	{
		if (format[i] == 'd' || format[i] == 'i' ) // ready
			return (handler_d(arg, e_sequence));
		else if (format[i]== 'f' || format[i]== 'F')
			return (handler_f(arg, e_sequence));
		else if (format[i] == 'c' || format[i] == 'C') 
			return (handler_c(arg, e_sequence));
		else if (format[i] == 's')
			return (handler_s(arg, e_sequence));
		else if (format[i] == 'p')
			return (handler_p(arg, e_sequence));
		else if (format[i] == 'u' || format[i] == 'U')
			return (handler_u(arg, e_sequence));
		else if (format[i] == 'o' || format[i] == 'O')
			return(handler_o(arg, e_sequence));
		else if (format[i] == 'x')
			return(handler_x(arg, e_sequence));
		else if (format[i] == 'X')
			return(handler_x_big(arg, e_sequence));
		else if (format[i] == '%') //  ready
			return (handler_percent(e_sequence));
	}
	return (NULL);
}

/*int		ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*string; // prepared string for print
	int		i;		// counter
	int		start;	// var to find pos after foramtting
	int		found_spec; // flag
	t_formatting *e_sequence;

	i = 0;
	string = ft_strnew(0);
	start = 0;
	found_spec = 0;
	va_start(arg, format);
	// нужна проверку на количество спецификаций с количеством аргументом
	while (format[i])
	{
		if (format[i] == '%' && !found_spec)
		{
			e_sequence = scanning_sequence(format + i + 1); // need to free
			found_spec = 1;
			string = ft_strfjoin(string, ft_strsub(format, start, i - start), 0);
			string = ft_strjoin(string, find_specifier(format + i, arg, e_sequence));
			//printf("length: %d\nspecifier: %c\n", e_sequence->common_length, e_sequence->specifier);
		}
		else if (found_spec)
		{
			if (find_end_spec(format[i]))
			{
				start = i + 1;
				found_spec = 0;			
			}
		}
		i++;
	}
	string = ft_strjoin(string, ft_strsub(format, start, i - start)); // проверить
	ft_putstr(string);
	va_end(arg);
	return (1);
}*/

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	char	*string; // prepared string for print
	char	*substr;
	int		i;		// counter
	int		start;	// var to find pos after foramtting
	int		found_spec; // flag
	t_formatting *e_sequence;
	size_t	common_length;

	common_length = 0;
	i = -1;
	string = ft_strnew(0);
	start = 0;
	found_spec = 0;
	va_start(arg, format);
	// нужна проверку на количество спецификаций с количеством аргументом
	while (format[++i])
	{
		if (format[i] == '%' && !found_spec)
		{
			/*e_sequence = scanning_sequence(format + i + 1); // need to free
			found_spec = 1;
			string = ft_strfjoin(string, ft_strsub(format, start, i - start), 0);
			substr = find_specifier(format + i, arg, e_sequence);
			common_length += e_sequence->common_length;
			//if (e_sequence->specifier == 'c' && e_sequence->common_length != ft_strlen(substr))
				
			string = ft_strjoin(string, substr);
			printf("length: %d\nspecifier: %c\n", e_sequence->common_length, e_sequence->specifier);*/
			
			e_sequence = scanning_sequence(format + i + 1); // need to free
			found_spec = 1;
			if (start == 0)
				string = ft_strljoin(string, ft_strsub(format, start, i - start), 0, i - start);
			else
				string = ft_strljoin(string, ft_strsub(format, start, i - start), common_length - (i - start), i - start);
			substr = find_specifier(format + i, arg, e_sequence);
			string = ft_strljoin(string, substr, common_length, e_sequence->common_length);
			common_length += e_sequence->common_length;
		}
		else if (found_spec)
		{
			if (find_end_spec(format[i]))
			{
				start = i + 1;
				found_spec = 0;			
			}
		}
		else
			common_length++;
	}
	string = ft_strljoin(string, ft_strsub(format, start, i - start), common_length - (i - start), (i - start)); // проверить
	write(1, string, common_length);
	va_end(arg);
	return (common_length);
}

t_ld_nbr *LDblAsForm(const long double number)
{
	t_ld_nbr		*forms;
    int				i;
    int 			len;
    unsigned long	num;
	
    len = 8*sizeof(long double) - 1;
    num = *(unsigned long*)&number;
	printf("%lu\nlen: %d\n", num, len);

	for (i = len; i >= 0; i--)
        printf("%zu", (num >> i) & 1);
    printf("\n");
	return(NULL);
}

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


void	PrintFracDecimal(unsigned long *massive)
{
	int		i;

	i = 0;
	while (i < 63)
	{
		printf("%lu\n", massive[i]);
		i++;
	}
}


char	*GetDecimalIntStr(char *bin)
{
	return (NULL);
}

char	*GetDecimalFracStr(char *frac_bin, t_str_fp *str)
{
	int		i;
	int		k;
	size_t	len;
	t_long_value	tmp;
	t_long_value	result;
	//char            fractional

	result.values = (int*)malloc(sizeof(int) * 1);
	result.values[0] = 0;
	result.length = 0;
	i = 0;
	/*str->dec_represent->frac = (char**)malloc(sizeof(char*) * 65);
	while (i < 64)
	{
			(str->dec_represent->frac)[i] = ft_strnew(100);
			i++;
	}*/
	i = 0;
	k = 1;
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
	str->frac = ConvBigNumToStr(result);
	PrintBigNum(result);
	printf("string: %s\n", str->frac);
	return (NULL);
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


char	*Get_Number(t_float *fp)
{
	long double		dec_number;
	unsigned long	dec_mantissa;
	int				exp;
	t_str_fp		*str;
	
	str = (t_str_fp*)malloc(sizeof(t_str_fp));
	//str->dec_represent = (struct bignum*)malloc(sizeof(struct bignum));
	exp = (BinAsDec(fp->exp) - 16383); // заменить
    printf("exp_binary: %s\nexp: %i\n", fp->exp, exp);
	if (exp >= 0) {
        str->integer = ft_strdup(&fp->int_part);
        str->integer = ft_strjoin(str->integer, ft_strsub(fp->frac, 0, exp));
        str->frac = ft_strsub(fp->frac, exp, 63 - exp);
        printf("int: %s\nfrac: %s\n", str->integer, str->frac);
        printf("decimal integer part: %lu\n", BinAsDec(str->integer));
        dec_number = pow(2, exp);
        dec_number *= (1 + (dec_mantissa / pow(2, 63)));
    }
	else{
	    str->integer = ft_strdup("0");
	    str->frac = ft_strjoin(&fp->int_part, fp->frac);
	    str->frac = ft_strjoin(GetLeadingZeros(abs(exp + 1)), str->frac);
	    printf("int: %s\nfrac: %s\n", str->integer, str->frac);
	}
	GetDecimalFracStr(str->frac, str);
	return (NULL);
}

int		main()
{
	char	*greeting = "Добрый вечер!";
	char	*name = "Artem";
	short age = 20;
	double	Pi = 3.14234567891234567;
	//double	i = 1.1;-
	float	a = 1.998607848473;


	t_float *fp;
	fp = Fill_FP((long double)0.0000005089);
	printf("binary: %s\n", fp->binary_represent);
	LDblAsForm((long double)1.3);
	Get_Number(fp);
	printf("original: %.8f\n", 0.0000005089);
    //printf("original: %.60f\n", 1234.78);

	//printf("rev: %s\n", ft_strrev(name));
	//ft_printf("Hel%")
	//ft_printf("Hello %5s`#!\nMy %came is %10.2s\n%p\n", "world", 'n', name, &name);
	/* ft_printf("I'm % .05 d лет\n", 20); // will right process
	printf("I'm % .05 d лет\n", 20);*/
	//printf("%\n", 5);Ba
	/*ft_printf("%.15.5.3.2.23.3.4 500 100 d\n", 2000); // space include in width, but not int precision
	printf("%.15.5.3.2.23.3.4. 500 -15 .10d\n", 2000); */
	/*ft_printf("number: %015.10d\n", 10);
	printf("number: %O\n%%\n", age);*/
	/*ft_printf("%+0 456 567 56 7 8 89 1.10 5ld\n", 5);
	printf("%+0 456 567 56 7 8 89 1.10 5ld\n", 5);
	ft_printf("%04.3d\n", -999); // 0 and precision
	printf("%04.3d\n", -999);*/
	//printf("lol%10.5l+d\n", 505);
	/*ft_printf("Hello %7s!\nMy %5came is %10.2s\n", "world", '\0', name);
	printf("Hello %0.0s!\nMy %5came is %10.2s\n", "world", '\0', name);*/
	
	//ft_printf("Hello %s.\nLetter is %10.5c.\n", "world", 'A');
	//printf("Hello %s.\nLetter is %.5c.\n", "world", 'A');
	//PrintDblAsBin1(5.0);
	//printf("convert: %lu\n", FractionBinAsDec("0110011001100110"));
	//ft_printf("number: %hd\n", 32768);
	//printf("number: %hd\n", 32768);
	//printf("number: %lu\n", (unsigned long int)18446744073709551615);
	//printf("size this string: %d |\n", printf("float: %.30f\n", Pi));
	//printf("size this string: %d |\n", printf("symbol: %\n", 0x100));
	//ft_printf("- Hello, dude! My name is %s. I'm %+05ld. How are you?\n%s\n", "Artem", age, "- Nice, thanks!");
	//printf("%s Меня зовут %-10s. Мне %+05hd лет.\n Число (int)Пи = %.0f, Pointer: %15p\n", greeting, name, age, Pi, greeting);
	
	//ft_printf("%-#10.5o\n", -16);
	//printf("%-10.0o", 0);
	//ft_printf("Age's address: %0.10p\n", &age);
	//printf("Age's adress: %p\n", &age);
	//printf("di: %.15f\n", (double)(i - 1.2));
	//printf("%3$i %i %i %i %5$i ", 10, 6, 7, 5, 4, 3);
	
	//printf("%.100f\n", 0.33589235903248509238958230532523523523598);
	//printf("%e\n", 6553.12412);

	//printf("%lf = %i %i %i %i %i %i %i %i\n", value.d, PIB(value.b[0]), value.b[1], value.b[2], value.b[3], value.b[4], value.b[5], value.b[6], value.b[7]);
	//printf("bin_str: %s\n", PresentIntAsBin(255));
	return (1);
}