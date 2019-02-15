/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qweissna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:37:08 by qweissna          #+#    #+#             */
/*   Updated: 2019/02/15 14:41:32 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

void	print_matrix(char **matrix)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		ft_putstr(matrix[i]);
		ft_putchar('\n');
	}
}

void	print_lists(tet_lst *begin)
{
	tet_lst	*cur_lst;

	cur_lst = begin;
	printf("Выводим все листы: \n");
	while (cur_lst)
	{
		print_matrix(cur_lst->tetrimino_matrix);
		ft_putchar('\n');
		cur_lst = cur_lst->next;
	}
}

void	print_tetris(char **tetris, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		ft_putstr(tetris[i]);
		ft_putchar('\n');
	}
}

void	print_pos(tet_coords *coords)
{
	int		k;

	while (coords)
	{
		k = -1;
		printf("********Coordinates************\n");
		printf("symbol: %c\n", coords->symbol);
		while (++k < 4)
			printf("point:\n\tx: %d\n\ty: %d\n", coords->pos[k][0], coords->pos[k][1]);
		printf("*******************************\n");
		coords = coords->next;
	}
}
