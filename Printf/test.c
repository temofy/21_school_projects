/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:02:30 by cheller           #+#    #+#             */
/*   Updated: 2019/04/16 15:46:57 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	nbr_len(int n)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_negative_max(char **str, int n)
{
	n = n + 1;
	*str = ft_itoa(n);
	(*str)[10] = '8';
	return (*str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

    if (n == -2147483648)
		return (ft_negative_max(&str, n));
	i = nbr_len(n);
	str = ft_strnew(i);
    i -= 1;
	if (!str)
		return (NULL);
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i--] = 48 + (n % 10);
		n /= 10;
	}
	return (str);
}

int     main()
{
    char *str;

    str = ft_itoa(-2147483648);
    printf("%s\n", "Hello, dude!");
    printf("max: %s\n", str);
    free(str);
    *str = '4';
    printf("after %s\n", str);
    return (1);
}