/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 12:37:04 by cheller           #+#    #+#             */
/*   Updated: 2019/08/24 12:37:07 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		record_links(t_map *map, char **file, int *i)
{
	static int	k = 0;
	int			seperator;

	seperator = 0;
	if (k == map->nbrs_links)
		return (-1);
	map->links[k].room1 = links_split(file[*i], 1, seperator);
	map->links[k].room2 = links_split(file[*i], 2, seperator);
	k++;
	return (1);
}

int		record_rooms(t_map *map, char **file, int *i, int amount)
{
	int j;

	if (ft_isthere_chr(file[*i], '#'))
	{
		if (handler_hashes(map, file, i) == -1)
			return (-1);
	}
	else if (!ft_isthere_chr(file[*i], '#'))
	{
		if (!(map->rooms))
		{
			map->rooms = ft_memalloc(sizeof(t_room) * amount);
			j = -1;
			while (++j < amount)
			{
				map->rooms[j].x = -1;
				map->rooms[j].y = -1;
			}
		}
		if (reading_rooms(file[*i], map) == -1)
			return (-1);
	}
	return (1);
}

int		handler_hashes(t_map *map, char **file, int *i)
{
	if (ft_strcmp("##start", file[*i]) == 0 && !(map->start))
	{
		if (reading_se(file[++*i], &(map->start)) == -1)
			return (-1);
		return (1);
	}
	else if (ft_strcmp("##start", file[*i]) == 0 && map->start)
		return (-1);
	else if (ft_strcmp("##end", file[*i]) == 0 && !(map->end))
	{
		if (reading_se(file[++*i], &(map->end)) == -1)
			return (-1);
		return (1);
	}
	else if (ft_strcmp("##end", file[*i]) == 0 && map->end)
		return (-1);
	return (1);
}

int		handler_links(t_map *map, char **file, int *i)
{
	map->nbrs_links = count_links(file, *i);
	if (!map->nbrs_rooms && (!map->start || !map->end))
		return (-1);
	while (file[*i] && (((ft_count_words(file[*i]) == 1) &&
		ft_isthere_chr(file[*i], '-')) || ft_isthere_chr(file[*i], '#')))
	{
		if (file[*i][0] == '#')
		{
			if (handler_hashes(map, file, i) == -1)
				return (-1);
		}
		else
		{
			if (!map->links)
				map->links = (t_links*)
						ft_memalloc(sizeof(t_links) * map->nbrs_links);
			if (record_links(map, file, i) == -1)
				return (-1);
		}
		(*i)++;
	}
	return (1);
}

t_node	*find_among_entrances(int found_next_i, t_node *cur_room)
{
	int i;
	int k;

	i = -1;
	while (++i < cur_room->entrances)
	{
		if (found_next_i == cur_room->prev_room[i]->i_room)
		{
			k = 0;
			while (k < cur_room->prev_room[i]->exits)
			{
				if (cur_room->prev_room[i]->next_room[k]->i_room
					== cur_room->i_room)
				{
					cur_room->prev_room[i]->next_for_bfs = k;
					cur_room->prev_room[i]->prev_for_bfs = -1;
				}
				k++;
			}
			return ((cur_room->prev_room[i]));
		}
	}
	return (NULL);
}
