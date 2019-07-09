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

	if (!string)
		return (-1);
	while (*string)
	{
		if (*string < '0' || *string > '9')
			return (-1);
		*ants = *ants * 10 + (*string - '0');
		string++;
	}
	return (1);
}

int 	reading_rooms(char *str, t_map *map)
{
	char		**room;
	static int	i = 0;
	long		*value;
	int 		rtn;

	rtn = (!str) ? -1 : 1;
	room = ft_strsplit(str, ' ');
	rtn = (rtn == 1 && room && room[0][0] == 'L') ? -1 : 1;
	if (rtn == 1 && map->rooms)
	{
		map->rooms[i].name = ft_strdup(room[0]);
		value = ft_atopi(room[1]); //учесть передачу адреса
		if (value)
			map->rooms[i].x = (int)*value;
		else
			rtn = -1;
		value = ft_atopi(room[2]); // учесть передачу адреса
		if (value)
			map->rooms[i].y = (int)*value;
		else
			rtn = -1;
		i++;
	}
	ft_arrdel(&room);
	return (rtn);
}

/*int 	reading_rooms(char *str, t_map *map)
{
	char		**room;
	static int	i = 0;
	long		*value;

	if (!str)
		return (-1);
	room = ft_strsplit(str, ' ');
	if (room[0][0] != 'L' && map->rooms)
	{
		map->rooms[i].name = ft_strdup(room[0]);
		value = ft_atopi(room[1]); //учесть передачу адреса
		if (value)
			map->rooms[i].x = (int)*value;
		else
			return (-1); // утечки
		value = ft_atopi(room[2]); // учесть передачу адреса
		if (value)
			map->rooms[i].y = (int)*value;
		else
			return (-1); // утечки
		i++;
	}
	ft_arrdel(&room);
	return (1);
}*/

int 	reading_se(char *str, t_room **se) // добавить очищение и на L проверку
{
	char		**room;
	long 		*value;
	int 		rtn;

	rtn = (!str || ft_count_words(str) != 3) ? -1 : 1;
	room = (rtn == 1) ? ft_strsplit(str, ' ') : NULL;
	*se = (rtn == 1) ? (t_room *) ft_memalloc(sizeof(t_room)) : NULL;
	rtn = (*se == NULL) ? -1 : 1;
	rtn = (rtn == 1 && room[0][0] == 'L') ? -1 : 1;
	if (rtn == 1)
	{
		(*se)->name = ft_strdup(room[0]);
		value = ft_atopi(room[1]);
		if (value)
			(*se)->x = (int) *value;
		else
			rtn = -1;
		value = ft_atopi(room[2]);
		if (value)
			(*se)->y = (int) *value;
		else
			rtn = -1;
	}
	ft_arrdel(&room);
	return (rtn);
}

int 	record_links(t_map *map, char **file, int *i, int links)
{
	char 	**values;

	values = ft_strsplit(file[*i], '-'); // оптимизировать без сплита
	map->links->room1 = ft_strdup(values[0]);
	map->links->room2 = ft_strdup(values[1]);
	ft_arrdel(&values);
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

int 	record_ants(t_map *map, char* string)
{
	if (map->ants == -1)
	{
		if (ft_count_words(string) == 1) // проверку на два числа
		{
			if (reading_ants(string, &(map->ants)) == -1)
				return (free_map(map, -1));
		}
		else
			return (free_map(map, -1));
	}
	return (1);
}

int 	handler_hashes(t_map *map, char **file, int *i)
{
	if (ft_strcmp("##start", file[*i]) == 0 && !(map->start))
	{
		if (reading_se(file[*i + 1], &(map->start)) == -1)
			return (-1);
		*i = *i + 1;
		return (1);
	}
	else if (ft_strcmp("##start", file[*i]) == 0 && map->start)
		return (-1);
	else if (ft_strcmp("##end", file[*i]) == 0 && !(map->end))
	{
		if (reading_se(file[*i + 1], &(map->end)) == -1)
			return (-1);
		*i = *i + 1;
		return (1);
	}
	else if (ft_strcmp("##end", file[*i]) == 0 && map->end)
		return (-1);
	return (1);
}

int 	record_rooms(t_map *map, char **file, int *i, int amount)
{
	if (ft_isthere_chr(file[*i], '#'))
	{
		if (handler_hashes(map, file, i) == -1)
			return (-1);
	}
	else if (!ft_isthere_chr(file[*i], '#'))
	{
		if (!(map->rooms))
			map->rooms = ft_memalloc(sizeof(t_room) * amount);
		if (reading_rooms(file[*i], map) == -1)
			return(-1);
	}
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
int 	check_map(t_map *map)
{
	if (non_repeatability_check(map) == -1)
		return (-1);
	return (1);
}

int 	handler_links(t_map *map, char **file, int *i)
{
	map->nbrs_links = count_links(file, *i);
	while (file[*i] && (((ft_count_words(file[*i]) == 1) && ft_isthere_chr(file[*i], '-')) || ft_isthere_chr(file[*i], '#')))
	{
		if (file[*i][0] == '#')
		{
			if (handler_hashes(map, file, i) == -1)
				return (-1); // утечка file
		}
		else
		{
			if (!map->links)
				map->links = (t_links *) ft_memalloc(sizeof(t_links) * map->nbrs_links);
			if (record_links(map, file, i, map->nbrs_links) == -1)
				return (-1); // утечки
		}
		(*i)++;
	}
	return (1);
}

int 	validate_record(t_map *map)
{
	char 	**file;
	int 	i;
	int 	rtn;

	file = ft_strsplit(map->file, '\n');
	i = 0;
	if (reading_ants(file[0], &(map->ants)) == -1)
		return (-1); // удалить массив
	map->nbrs_rooms = count_rooms(file, i + 1);
	while (file[++i] && ((ft_count_words(file[i]) == 3) || ft_isthere_chr(file[i], '#')))
	{
		if (record_rooms(map, file, &i, map->nbrs_rooms) == -1)
		{
			ft_arrdel(&file);
			return (-1);
		}
	}
	handler_links(map, file, &i);
	if (file[i] != NULL || !map->start || !map->end)
		rtn = -1;
	else
		rtn = check_map(map);
	ft_arrdel(&file);
	return (rtn);
}

/*int 	validate_record(t_map *map)
{
	char 	**file;
	int 	i;
	int 	links;

	file = ft_strsplit(map->file, '\n');
	i = 0;

	if (reading_ants(file[0], &(map->ants)) == -1)
		return (-1); // удалить массив
	while ((ft_count_words(file[++i]) == 3) || ft_isthere_chr(file[i], '#'))
	{
		if (record_rooms(map, file, &i) == -1)
		{} // удалить массив
	}
	links = count_links(file, i);
	while ((ft_count_words(file[i]) == 1) && ft_isthere_chr(file[i], '-'))
	{
		if (!map->links)
			map->links = (t_links*)ft_memalloc(sizeof(t_links) * links);
		if (record_links(map, file, &i, links) == -1)
		{}
		i++;
	}
	if (file[i] != NULL || !map->start || !map->end)
		return (-1); // утечка
	 ft_arrdel(&file);
	return (1);
}*/

int		reading_map()
{
	char  	*string;
	t_map	map;

	initialize_map(&map);
	map.file = ft_strnew(0);
	while (get_next_line(0, &string))
	{
		map.file = ft_strfjoin(map.file, string, 0);
		map.file = ft_strfjoin(map.file, "\n", 1);
	}
	if(validate_record(&map) == -1)
		return (free_map(&map, -1));
	//printf("%s", map.file);
	//printf("size: %i\n", ft_arraylen((void**)map.rooms));
	return (1);
}
