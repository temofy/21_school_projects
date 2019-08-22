/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:49:19 by cheller           #+#    #+#             */
/*   Updated: 2019/08/22 20:49:22 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int 	check_map(t_map *map, char ***ways, t_node2 **first_room)
{
	char	**directed_ways;

	if (non_repeatability_check(map) == -1)
		return (-1);
	if (check_coordinates(map) == -1)
		return (-1);
	if (make_validate_ways(map, ways) == -1)
		return (-1);
	directed_ways = set_the_direction(*ways, map);
	*first_room = create_nodes(map, directed_ways);
	ft_arrdel(&directed_ways);
	return (1);
}

int 	non_repeatability_check(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->nbrs_rooms)
	{
		j = 0;
		j = (i == j) ? j + 1 : j;
		while (j < map->nbrs_rooms - 1)
		{
			j = (i == j) ? j + 1 : j;
			if (ft_strcmp(map->rooms[i].name, map->rooms[j++].name) == 0)
				return (-1);
		}
		if (ft_strcmp(map->start->name, map->rooms[i].name) == 0)
			return (-1);
		if (ft_strcmp(map->end->name, map->rooms[i].name) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int 	check_vertex_entry(char **ways, int vertex, t_map *map)
{
	int	i;

	i = 0;
	while(i < map->nbrs_rooms + 2)
	{
		if (ways[i][vertex] == '2')
			return (1);
		i++;
	}
	return (0);
}

int		check_coordinates(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->nbrs_rooms)
	{
		j = 0;
		while (j < map->nbrs_rooms)
		{
			if (j == i)
			{
				j++;
				continue;
			}
			if (map->rooms[i].x == map->rooms[j].x &&
				map->rooms[i].y == map->rooms[j].y)
				return (-1);
			j++;
		}
		if (map->rooms[i].x == map->start->x &&
			map->rooms[i].y == map->start->y)
			return (-1);
		if (map->rooms[i].x == map->end->x && map->rooms[i].y == map->end->y)
			return (-1);
		i++;
	}
	return (1);
}