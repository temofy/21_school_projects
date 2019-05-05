/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:41:08 by cheller           #+#    #+#             */
/*   Updated: 2019/04/29 12:43:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void PrintDblAsBin1(const double number)
{
    int  i;
    int  len;
    unsigned long  num;
    len = 8*sizeof(double) - 1;
    num = *(unsigned long*)&number;
	printf("%lu\nlen: %d\n", num, len);
	//printf("bit: %zu\n", (num >> 62) & 1);
    for (i = len; i >= 0; i--)
        printf("%zu", (num >> i) & 1);
    printf("\n");
}