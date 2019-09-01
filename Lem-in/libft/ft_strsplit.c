/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:18:29 by cheller           #+#    #+#             */
/*   Updated: 2018/12/28 14:57:08 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sum_words(char const *s, char c)
{
	int		words;
	int		find_word;
	int		i;

	i = 0;
	words = 0;
	find_word = 0;
	while (s[i])
	{
		if (s[i] != c && !find_word)
		{
			find_word = 1;
			words++;
		}
		else if (s[i] == c)
			find_word = 0;
		i++;
	}
	return (words);
}

static int	get_word_len(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;
	int		word;
	int		words;

	i = -1;
	word = -1;
	if (!s || !(strs = (char**)malloc(sizeof(char*) * (sum_words(s, c) + 1))))
		return (NULL);
	words = sum_words(s, c);
	while (s[++i] && word < words)
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			if (!(strs[++word] = ft_strnew(get_word_len(&s[i], c))))
				return (NULL);
			j = 0;
		}
		if (s[i] != c)
			strs[word][j++] = (char)s[i];
	}
	strs[++word] = NULL;
	return (strs);
}
