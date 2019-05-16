/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 17:23:51 by cheller           #+#    #+#             */
/*   Updated: 2019/03/18 14:02:49 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char *s1, char *s2, int arg_to_free)
{
	if (arg_to_free == 1)
		free(s1);
	else if (arg_to_free == 2)
		free(s2);
	else if (arg_to_free == 0)
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strfjoin(char *s1, char *s2, int arg_to_free)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (!(str = ft_strnew(len_s1 + len_s2)))
		return (NULL);
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		str[i] = s2[i - len_s1];
		i++;
	}
	ft_free(s1, s2, arg_to_free);
	return (str);
}
