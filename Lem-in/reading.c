/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:42:49 by cheller           #+#    #+#             */
/*   Updated: 2019/06/29 19:42:50 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int 	reading_ants(char *string, int *ants)
{
	*ants = 0;

	while (*string)
	{
		if (*string < '0' || *string > '9')
			return (-1);
		*ants = *ants * 10 + (*string - '0');
		string++;
	}
	return (1);
}

int 	free_map(t_map *map, int status)
{
	if (map->rooms != NULL)
		free(map->rooms);
	if (map->links != NULL)
		free(map->links);
	if (map->start != NULL)
		free(map->start);
	if (map->end != NULL)
		free(map->end);
	map->rooms = NULL;
	map->links = NULL;
	map->start = NULL;
	map->end = NULL;
	return (status);
}

int 	reading_rooms(char *str, t_map *map)
{
	char **room;

	if (!str)
		return (-1);
	room = ft_strsplit(str, ' ');
	while (*str)
	{
		break ;
	}
	return (1);
}

int 	reading_end(char *str, t_map *map)
{
	return (1);
}

int 	reading_start(char *str, t_map *map)
{
	return (1);
}

int 	reading_links(char *str, t_map *map)
{
	return (1);
}

void	initialize_map(t_map *map)
{
	map->ants = -1;
	map->rooms = NULL;
	map->links = NULL;
	map->start = NULL;
	map->end = NULL;
}

int		reading_map()
{
	char  	*string;
	int 	start_room;
	int 	end_room;
	t_map	map;

	initialize_map(&map);
	start_room = -1;
	end_room = -1;
	while (get_next_line(0, &string))
	{
		if (map.ants == -1)
		{
			if (ft_count_words(string) == 1) // проверку на два числа
			{
				if (reading_ants(string, &(map.ants)) == -1)
					return (free_map(&map, -1));
			}
			else
				return (free_map(&map, -1));
		}
		else if (ft_count_words(string) == 1 && !ft_isthere_chr(string, '#') && !ft_isthere_chr(string, '-'))
			return (free_map(&map, -1));

		if (ft_strcmp("##start", string) == 0 && start_room == -1)
			start_room = 1;
		else if (ft_strcmp("##start", string) == 0 && !start_room)
			return (free_map(&map, -1));
		else if (start_room == 1)
		{
			if (reading_start(string, &map) == -1)
				return (free_map(&map, -1));
			start_room--;
		}


		if (ft_strcmp("##end", string) == 0 && end_room == -1)
			end_room = 1;
		else if (ft_strcmp("##end", string) == 0 && !end_room)
			return (free_map(&map, -1));
		if (end_room == 1)
		{
			if (reading_end(string, &map) == -1)
				return (free_map(&map, -1));
			end_room--;
		}

		if (ft_count_words(string) == 3)
		{
			reading_rooms(string, &map);
		}
		else if (ft_isthere_chr(string, '-') == 1)
		{
			reading_links(string, &map);
		}
		else
			return (free_map(&map, -1));
	}
	return (1);
}
