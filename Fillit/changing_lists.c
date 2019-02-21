/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   changing_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:03:54 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 19:04:51 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			return_start_pos(t_tet_coords *coord)
{
	int		left_vertex;
	int		top_vertex;
	int		i;

	left_vertex = find_left_vertex(coord);
	top_vertex = find_top_vertex(coord);
	while (left_vertex)
	{
		i = -1;
		while (++i < 4)
			coord->pos[i][0]--;
		left_vertex--;
	}
	while (top_vertex)
	{
		i = -1;
		while (++i < 4)
			coord->pos[i][1]--;
		top_vertex--;
	}
}

int				move_tet(t_tet_coords *coord, int size)
{
	int		wall;
	int		i;

	i = -1;
	wall = find_right_vertex(coord);
	if (wall + 1 != size)
		while (++i < 4)
			coord->pos[i][0] += 1;
	else if (wall + 1 == size)
	{
		wall = find_bottom_vertex(coord);
		if (wall + 1 == size)
			return (-1);
		i = -1;
		while (++i < 4)
			coord->pos[i][1] += 1;
		wall = find_left_vertex(coord);
		while (wall-- > 0)
		{
			i = -1;
			while (++i < 4)
				coord->pos[i][0]--;
		}
	}
	return (1);
}
