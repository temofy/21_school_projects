/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_with_ways.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:57:37 by cheller           #+#    #+#             */
/*   Updated: 2019/08/23 20:57:39 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	record_shortest_way(char **ways, t_node *end)
{
	while (end->prev_room)
	{
		if (end->prev_for_bfs == -1)
		{
			ways[end->next_room[end->next_for_bfs]->i_room][end->i_room] = '2';
			end = end->next_room[end->next_for_bfs];
		}
		else
		{
			ways[end->prev_room[end->prev_for_bfs]->i_room][end->i_room] = '2';
			end = end->prev_room[end->prev_for_bfs];
		}
	}
}

int		make_validate_ways(t_map *map, char ***adjacency_matrix)
{
	int	i;
	int	room1;
	int	room2;

	*adjacency_matrix = ft_strmatrix(map->nbrs_rooms + 2, map->nbrs_rooms + 2);
	i = 0;
	while (i < map->nbrs_rooms + 2)
		ft_memset((*adjacency_matrix)[i++], 48, map->nbrs_rooms + 2);
	i = 0;
	while (i < map->nbrs_links)
	{
		if ((room1 = find_index_room(map, map->links[i].room1)) == -1)
			return (-1);
		if ((room2 = find_index_room(map, map->links[i].room2)) == -1)
			return (-1);
		if ((*adjacency_matrix)[room1][room2] == '1' ||
			(*adjacency_matrix)[room2][room1] == '1')
			return (-1);
		(*adjacency_matrix)[room1][room2] = '1';
		(*adjacency_matrix)[room2][room1] = '1';
		i++;
	}
	return (1);
}

void	disable_crossing_ways(char **ways)
{
	int i;
	int j;

	i = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j])
		{
			if (ways[i][j] == '2' && ways[j][i] == '2')
			{
				ways[i][j] = '0';
				ways[j][i] = '0';
			}
			j++;
		}
		i++;
	}
}

int		finding_non_intersecting_ways(t_map *map, t_node *first)
{
	while (bfs(map, first) == 1)
	{
	}
	disable_crossing_ways(map->ways);
	map->amount_ways = count_non_intersecting_ways(map->ways);
	if (!(map->amount_ways))
		return (-1);
	print_farms_compos(map);
	launch_ants(map);
	return (1);
}
