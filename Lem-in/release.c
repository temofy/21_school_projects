/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:40:02 by cheller           #+#    #+#             */
/*   Updated: 2019/08/25 12:40:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_map_addition(t_map *map)
{
	if (map->start != NULL)
	{
		free(map->start->name);
		free(map->start);
	}
	if (map->end != NULL)
	{
		free(map->end->name);
		free(map->end);
	}
	ft_arrdel(&map->file);
	map->rooms = NULL;
	map->links = NULL;
	map->start = NULL;
	map->end = NULL;
	free_paths(&(map->paths), map->amount_ways);
	ft_arrdel(&(map->ways));
}

int		free_map(t_map *map, int status)
{
	int i;

	i = -1;
	if (map->rooms != NULL)
	{
		while (++i < map->nbrs_rooms)
			free(map->rooms[i].name);
		free(map->rooms);
	}
	if (map->links != NULL)
	{
		i = -1;
		while (++i < map->nbrs_links)
		{
			free(map->links[i].room1);
			free(map->links[i].room2);
		}
		free(map->links);
	}
	free_map_addition(map);
	return (status);
}

void	free_paths(t_paths **paths, int amount)
{
	int i;

	i = -1;
	if (paths && *paths)
	{
		while (++i < amount)
			free((*paths)[i].room);
		free(*paths);
		*paths = NULL;
	}
}

void	free_rooms(t_node **first_room, int amount_rooms)
{
	int i;

	if (!(*first_room))
		return ;
	i = -1;
	while (++i < amount_rooms)
	{
		if ((*first_room)[i].next_room)
			free((*first_room)[i].next_room);
		if ((*first_room)[i].prev_room)
			free((*first_room)[i].prev_room);
	}
	free(*first_room);
}

void	free_bfc(t_queue **q, char *checked)
{
	while (*q)
		queue_pop(q);
	free(checked);
}
