/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:50:21 by cheller           #+#    #+#             */
/*   Updated: 2019/03/15 17:50:56 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int num_hex_len(long int n)
{
    int i;

    i = 0;
    while (n > 0)
    {
        n = n/16;
        i++;
    }
    return (i);
}

char *hex_long_int(long int n)
{
    int i;
    int *res;
    char *c_res;
    long int tmp = n;

    i = num_hex_len(n) - 1;
    if (n == 0 && (c_res = (char*)malloc(sizeof(char) * 1)))
    {
    *c_res = '0';
    return (c_res);
    }
    if (!(res = (int*)malloc(sizeof(long int)*num_hex_len(n))) || !(c_res = (char*)malloc(sizeof(char)*num_hex_len(n))))
    return (NULL);
    while (i >= 0)
    {
    res[i] = n%16;
    i--;
    n = n/16;
    }
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