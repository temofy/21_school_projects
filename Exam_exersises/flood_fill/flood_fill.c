/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:51:48 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 20:53:25 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point.h"
#include <stdio.h>

void	flood_fill(char **tab, t_point size, t_point begin)
{
	t_point	tmp;
	char		chr;

	chr = tab[begin.x][begin.y];
	if (tab[begin.x][begin.y] == chr)
	{
		tab[begin.x][begin.y] = 'F';
		if (tab[begin.x][begin.y + 1] == chr)
		{
			tmp.x = begin.x;
			tmp.y = begin.y + 1;
			flood_fill(tab, size, tmp);
		}
		if (tab[begin.x + 1][begin.y] == chr)
		{
			tmp.x = begin.x + 1;
			tmp.y = begin.y;
			flood_fill(tab, size, tmp);
		}
		if (tab[begin.x - 1][begin.y] == chr)
		{
			tmp.x = begin.x - 1;
			tmp.y = begin.y;
			flood_fill(tab, size, tmp);
		}
		if (tab[begin.x][begin.y - 1] == chr)
		{
			tmp.x = begin.x;
			tmp.y = begin.y - 1;
			flood_fill(tab, size, tmp);
		}
	}
}

void	test(int i, char begin)
{
	static char chr;
	char	h;

	if (!chr)
		chr = begin;
	printf("chr: %c\n", chr);
	if (!i)
	{
		i = 1;
		test(i, 'B');
	}
	printf("h: %c\n", h);
}

int main()
{
	test(0, 'A');
	return (1);
}
