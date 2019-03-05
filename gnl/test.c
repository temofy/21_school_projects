/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:17:19 by cheller           #+#    #+#             */
/*   Updated: 2019/02/12 13:31:14 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		main(void)
{
	char	*str;
	char	*tmp;

	tmp = NULL;
	//str = ft_strnew(10);
	str = "It's New Line\n";
	tmp = ft_strdup("\0");
	printf("%s\n", tmp);
	printf("Строка до: %sEnd\n", tmp);
//	tmp = ft_strpchr(str, '\n');
	///printf("Строка после: %s\n", tmp);
	//free(str);
	free(tmp);
	//tmp = ft_strnew(10); 
	//free(tmp);
	return (1);
}
