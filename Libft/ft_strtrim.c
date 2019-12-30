/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:26:41 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 15:07:28 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_end(char const *s)
{
	size_t		found_ending;
	size_t		i;

	i = ft_strlen(s) - 1;
	found_ending = 0;
	if (!s)
		return (0);
	while (!found_ending && i > 0)
	{
		if (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
			i--;
		else
			found_ending = 1;
	}
	if (i == 0)
		return (ft_strlen(s));
	return (i);
}

static size_t	find_begin(char const *s)
{
	size_t		found_beginning;
	size_t		i;

	found_beginning = 0;
	i = 0;
	if (!s)
		return (0);
	while (!found_beginning && i < ft_strlen(s))
	{
		if ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && !found_beginning)
			i++;
		else
			found_beginning = 1;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char		*str;
	size_t		i;
	size_t		j;

	j = 0;
	i = find_begin(s);
	if (!s)
		return (NULL);
	str = ft_strnew(find_end(s) - find_begin(s) + 1);
	if (!str)
		return (NULL);
	while (s[i] && i <= find_end(s))
	{
		str[j] = (char)s[i];
		j++;
		i++;
	}
	return (str);
}
