/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 11:54:48 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 12:55:16 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*str_capitalize(char *str)
{
	int		word;
	int		i;

	i = -1;
	word = 0;
	while (str[++i])
	{
		if (((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')))
		{
			if ((str[i] >= 'a' && str[i] <= 'z') && !word)
				str[i] -= 32;
			else if ((str[i] >= 'A' && str[i] <= 'Z') && word)
				str[i] += 32;
			word = 1;
		}
		else if (str[i] == '\t' || str[i] == ' ')
			word = 0;
		else
			word = 1;
	}
	return (str);
}

void	ft_putstr(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
}

int		main(int argc, char *argv[])
{
	int		i;

	i = 1;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (1);
	}
	else
	{
		while (i < argc)
		{
			str_capitalize(argv[i]);
			ft_putstr(argv[i]);
			i++;
		}
	}
	return (1);
}
