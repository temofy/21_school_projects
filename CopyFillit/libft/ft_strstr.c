/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 19:26:36 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 15:52:25 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hys, const char *need)
{
	int		i;
	int		j;

<<<<<<< HEAD:gnl/test.c
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
=======
	i = 0;
	if (ft_strlen(need) == 0)
		return ((char*)hys);
	while (hys[i])
	{
		j = 0;
		while (need[j] == hys[i + j])
		{
			if (need[j + 1] == '\0')
				return ((char*)hys + i);
			j++;
		}
		i++;
	}
	return (NULL);
>>>>>>> bd900c13445c6590bfb15756eb36a6f417607dcc:CopyFillit/libft/ft_strstr.c
}
