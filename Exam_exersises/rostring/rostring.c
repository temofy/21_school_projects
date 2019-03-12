/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:59:12 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 15:54:03 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*make_str(char *argv, int begin, int first_len)
{
	char	*str;
	int		length;
	int		one_space;
	int		i;
	int		j;

	i = begin;
	length = 0;
	one_space = 0;
	while (argv[++i + 1])
	{
		if ((argv[i] != ' ' && argv[i] != '\t'))
		{
			one_space = 0;
			length++;
		}
		else if((argv[i] == ' ' || argv[i] == '\t') && !one_space)
		{
			length++;
			one_space = 1;
		}
	}
	if ((argv[i] != ' ' && argv[i] != '\t'))
		length++;
	str = (char*)malloc(sizeof(char) * length + first_len + 2);
	str[length + first_len + 1] = '\0';

	one_space = 0;
	i = begin;
	j = -1;
	while (argv[++i])
	{
		if ((argv[i] != ' ' && argv[i] != '\t'))
		{
			str[++j] = argv[i];
			one_space = 0;
			length++;
		}
		else if((argv[i] == ' ' || argv[i] == '\t') && !one_space)
		{
			str[++j] = argv[i];
			one_space = 1;
		}
	}
	return (str);
}

char	*merge(char *str, char *argv, char *word, int begin, int length)
{

}

char	*rostring(char *argv)
{
	char	*str;
	char	*word;
	int		first_chr;
	int		i;
	int		length;

	i = -1;
	first_chr = -1;
	length = 0;
	while (argv[++i])
	{
		if ((argv[i] != ' ' && argv[i] != '\t'))
		{
			length++;
			if (first_chr == -1)
				first_chr = i;
		}
		else if ((argv[i] == ' ' || argv[i] == '\t') && first_chr != -1)
			break;
	}
	word = (char*)malloc(sizeof(char) * length + 1);
	word[length] = '\0';

	str = make_str(argv, i, length);
	i = -1;
	while (++i < length)
		word[i] = argv[first_chr++];


	i = -1;
	return (str);
}

int		main(int argc, char *argv[])
{
	char	*str;
	int		i;

	i = 1;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (i < argc)
	{
		str = rostring(argv[i]);
		i++;
	}
	return (1);
}
