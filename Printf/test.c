/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:02:30 by cheller           #+#    #+#             */
/*   Updated: 2019/05/06 13:48:51 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>

/*float	ft_pow(double number, double exp)
{
	double	result;

	result = number;
	while (exp > 1)
	{
		 result *= number;
		 exp--;
	}
	return (result);
}*/

char	*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = strlen((const char*)str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		j--;
		i++;
	}
	return (str);
}

int     main()
{
	char	*str;
	int 	array[3] = {1,2,3};
	int		array2[4];

	memcpy(array2, array, 12);
	printf("number: %i\n", array2[3]);
	//str = (char*)malloc(sizeof(char) * 6);
	
	str = strdup("Artem");
	//printf("ft_pow: %f\n", ft_pow(5, -3));
	printf("pow: %f\n", pow(2, -3));
	printf("rev: %s\n", ft_strrev(str));
    return (1);
}