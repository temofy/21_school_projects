/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:31:24 by cheller           #+#    #+#             */
/*   Updated: 2019/08/22 20:31:26 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_last_busy_room(t_paths *paths)
{
	int i;

	i = paths->amount_steps - 1;
	while (i > -1)
	{
		if (paths->room[i].ant_no > 0)
			return (i);
		i--;
	}
	return (-1);
}

t_num_q	*find_end_of_n_queue(t_num_q *q)
{
	while (q->next_in_q)
		q = q->next_in_q;
	return (q);
}

int		find_next_i(char **ways, int *neighbour, int vertex_i, char *checked)
{
	(*neighbour)++;
	while (ways[vertex_i][*neighbour])
	{
		if (ways[vertex_i][*neighbour] == '1' && checked[*neighbour] != '1')
			return (*neighbour);
		(*neighbour)++;
	}
	return (-1);
}

int		find_index_room(t_map *map, char *room)
{
	int i;

	i = 0;
	if (ft_strcmp(map->start->name, room) == 0)
		return (i);
	i++;
	while (i - 1 < map->nbrs_rooms)
	{
		if (ft_strcmp(map->rooms[i - 1].name, room) == 0)
			return (i);
		i++;
	}
	if (ft_strcmp(map->end->name, room) == 0)
		return (i);
	return (-1);
}

int		find_next_without_check(char **ways, int *neighbour, int vertex_i)
{
	(*neighbour)++;
	while (ways[vertex_i][*neighbour])
	{
		if (ways[vertex_i][*neighbour] == '1')
			return (*neighbour);
		(*neighbour)++;
	}
	return (-1);
}
