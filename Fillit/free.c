/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:02:16 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 17:03:53 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	zero_tetris(char **tetris, t_tet_coords *coord)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (POINT == coord->symbol)
			POINT = '.';
	}
}

void	zero_positions(t_tet_coords *positions)
{
	t_tet_coords	*cur;

	cur = positions;
	while (cur)
	{
		return_start_pos(cur);
		cur = cur->next;
	}
}

void	free_tetris(char **tetris, int size)
{
	while (size--)
		free(tetris[size]);
	free(tetris);
}

void	free_tetriminos(t_tet_coords *tetriminos)
{
	t_tet_coords	*next;

	while (tetriminos)
	{
		next = tetriminos->next;
		free(tetriminos);
		tetriminos = next;
	}
}
