/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_vertices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:58:30 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 19:08:00 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		find_right_vertex(t_tet_coords *coord)
{
	int		right_vertex;
	int		i;

	i = -1;
	right_vertex = 0;
	while (++i < 4)
	{
		if (coord->pos[i][0] > right_vertex)
			right_vertex = coord->pos[i][0];
	}
	return (right_vertex);
}

int		find_left_vertex(t_tet_coords *coord)
{
	int		left_vertex;
	int		i;

	i = 0;
	left_vertex = coord->pos[0][0];
	while (++i < 4)
	{
		if (coord->pos[i][0] < left_vertex)
			left_vertex = coord->pos[i][0];
	}
	return (left_vertex);
}

int		find_top_vertex(t_tet_coords *coord)
{
	int		top_vertex;
	int		i;

	i = 1;
	top_vertex = coord->pos[0][1];
	while (++i < 4)
	{
		if (coord->pos[i][1] < top_vertex)
			top_vertex = coord->pos[i][1];
	}
	return (top_vertex);
}

int		find_bottom_vertex(t_tet_coords *coord)
{
	int		bottom_vertex;
	int		i;

	i = -1;
	bottom_vertex = 0;
	while (++i < 4)
	{
		if (coord->pos[i][1] > bottom_vertex)
			bottom_vertex = coord->pos[i][1];
	}
	return (bottom_vertex);
}
