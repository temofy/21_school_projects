/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_tet.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qweissna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 20:47:51 by qweissna          #+#    #+#             */
/*   Updated: 2019/02/05 15:54:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			check_block(char *line)
{
	int		s;
	int		i;

	s = 0;
	i = 0;
	while (i < 20)
	{
		if (line[i] == '#')
		{
			if (line[i - 1] == '#' && (i - 1) >= 0)
				s++;
			if (line[i + 1] == '#' && (i + 1) < 20)
				s++;
			if (line[i - 5] == '#' && (i - 5) >= 0)
				s++;
			if (line[i + 5] == '#' && (i + 5) < 20)
				s++;
		}
		i++;
	}
	if (s == 6 || s == 8)
		return (1);
	return (-1);
}

int			nbrhood(int dots, int sharp, char *pt)
{
	if (dots != 12 || sharp != 4)
		return (-1);
	else
		return (check_block(pt));
}

int			validate(char *line)
{
	int		sharp;
	int		dots;
	int		x;
	int		y;
	int		sum;
	char	*pt;

	sum = 0;
	while (line)
	{
		y = 0;
		pt = line;
		dots = 0;
		sharp = 0;
		while (y < 4)
		{
			x = 0;
			while (x < 4)
			{
				if (*line == '.')
					dots++;
				else if (*line == '#')
					sharp++;
				else if (*line != '.' || *line != '#')
					return (-1);
				x++;
				line++;
			}
			if (*line != '\n')
				return (-1);
			if (++y == 4)
				break ;
			line++;
		}
		if (nbrhood(dots, sharp, pt) < 0)
			return (-1);
		line++;
		if (*line == '\0')
			return (sum + 1);
		sum++;
		if (!(*line == '\n'))
			return (-1);
		line++;
	}
	return (-1);
}
