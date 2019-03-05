/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:14:25 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 19:29:48 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			record_coords(t_tet_coords *cur_lst, char *str_tetriminos)
{
	int		y;
	int		x;
	int		k;

	y = -1;
	k = 0;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (*str_tetriminos == '#')
			{
				cur_lst->pos[k][0] = x;
				cur_lst->pos[k++][1] = y;
			}
			str_tetriminos++;
		}
		str_tetriminos++;
	}
}

t_tet_coords	*tet_init_pos(char *str_tetriminos, int amount)
{
	char			chr;
	t_tet_coords	*begin;
	t_tet_coords	*cur_lst;

	chr = 'A';
	begin = (t_tet_coords*)malloc(sizeof(t_tet_coords));
	begin->prev = NULL;
	cur_lst = begin;
	while (amount--)
	{
		cur_lst->symbol = chr++;
		record_coords(cur_lst, str_tetriminos);
		str_tetriminos += 21;
		return_start_pos(cur_lst);
		if (amount)
		{
			cur_lst->next = (t_tet_coords*)malloc(sizeof(t_tet_coords));
			(cur_lst->next)->prev = cur_lst;
			cur_lst = cur_lst->next;
		}
		else
			cur_lst->next = NULL;
	}
	return (begin);
}

int				place_tet(t_tet_coords *coord, char **tetris, int size)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (tetris[coord->pos[i][1]][coord->pos[i][0]] == '.')
			tetris[coord->pos[i][1]][coord->pos[i][0]] = (char)coord->symbol;
		else
		{
			zero_tetris(tetris, coord);
			if (move_tet(coord, size) == -1)
			{
				return_start_pos(coord);
				return (-1);
			}
			i = -1;
		}
	}
	return (1);
}

int				arrange(t_tet_coords *coord, char **tetris, int size)
{
	if (coord == NULL)
		return (1);
	if (place_tet(coord, tetris, size) == -1)
		return (-1);
	if (arrange(coord->next, tetris, size) == -1)
	{
		zero_tetris(tetris, coord);
		if (move_tet(coord, size) == -1)
		{
			return_start_pos(coord);
			return (-1);
		}
		if (arrange(coord, tetris, size) == -1)
			return (-1);
	}
	return (1);
}

int				check_tet_length(t_tet_coords *tetrimino)
{
	int				length;
	int				i;
	t_tet_coords	*cur_lst;

	cur_lst = tetrimino;
	length = 0;
	while (cur_lst)
	{
		i = -1;
		while (++i < 4)
		{
			if (length < cur_lst->pos[i][0])
				length = cur_lst->pos[i][0];
			if (length < cur_lst->pos[i][1])
				length = cur_lst->pos[i][1];
		}
		cur_lst = cur_lst->next;
	}
	return (length + 1);
}
