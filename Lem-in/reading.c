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
	char		**room;
	static int	i = 0;

	if (!str)
		return (-1);
	room = ft_strsplit(str, ' ');
	if (map->rooms)
	{
		//map->rooms = (t_room*)malloc(sizeof(t_room) * 2);
		map->rooms[i].name = ft_strdup(room[0]);
		if (!(map->rooms[i].x = (int)*ft_atopi(room[1])))
			return (-1);
		if (!(map->rooms[i].y = (int)*ft_atopi(room[2])))
			return (-1);
		i++;
		//map->room = NULL;
	}
	ft_arrdel(&room);
	return (1);
}

int 	reading_end(char *str, t_map *map)
{
	char		**room;

	if (!str)
		return (-1);
	/*if (ft_count_words(str) != 3)
		return (-1);*/
	room = ft_strsplit(str, ' ');
	if (!(map->end = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	map->end->name = room[0];
	if (!(map->end->x = (int)*ft_atopi(room[1])))
		return (-1);
	if (!(map->end->y = (int)*ft_atopi(room[2])))
		return (-1);
	ft_arrdel(&room);
	return (1);
}

int 	reading_start(char *str, t_map *map)
{
	char		**room;

	if (!str)
		return (-1);
	/*if (ft_count_words(str) != 3)
		return (-1);*/
	room = ft_strsplit(str, ' ');
	if (!(map->start = (t_room*)ft_memalloc(sizeof(t_room))))
		return (-1);
	map->start->name = room[0];
	if (!(map->start->x = (int)*ft_atopi(room[1])))
		return (-1);
	if (!(map->start->y = (int)*ft_atopi(room[2])))
		return (-1);
	ft_arrdel(&room);
	return (1);
}

int 	record_links(t_map *map, char **file, int *i, int links)
{
	char 	**values;
	static int k = 0;

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

int 	record_rooms(t_map *map, char **file, int *i)
{

	if (ft_strcmp("##start", file[*i]) == 0 && !(map->start))
	{
		if (reading_start(file[*i + 1], map) == -1)
			return (free_map(map, -1));
		*i = *i + 1;
		return (1);
	}
	else if (ft_strcmp("##start", file[*i]) == 0 && map->start)
		return (free_map(map, -1));
	else if (ft_strcmp("##end", file[*i]) == 0 && !(map->end))
	{
		if (reading_end(file[*i + 1], map) == -1)
			return (free_map(map, -1));
		*i = *i + 1;
		return (1);
	}
	else if (ft_strcmp("##end", file[*i]) == 0 && map->end)
		return (free_map(map, -1));
	else if (!ft_isthere_chr(file[*i], '#'))
	{
		if (!(map->rooms))
			map->rooms = ft_memalloc(sizeof(t_room) * (map->ants - 2));
		if (reading_rooms(file[*i], map) == -1)
			return(free_map(map, -1));
	}
	return (1);
}

int 	count_links(char **file, int i)
{
	int		links;

	links = 0;
	while (file[i] && ft_count_words(file[i]) == 1 && ft_isthere_chr(file[i++], '-'))
		links++;
	/*if (file[i] != NULL)
		return (-1);*/
	return (links);
}

int 	non_repeatability_check(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->ants)
	{
		j = 0;
		j = (i == j) ? j + 1 : j;
		while (j < map-)
		if (ft_strcmp(map->rooms[i].name, map->rooms[j].name) == 0)
		{
			return (-1);
		}
	}
	return (1);
}

int 	validate_record(t_map *map)
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
}

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
		return (-1);
	//printf("%s", map.file);
	//printf("size: %i\n", ft_arraylen((void**)map.rooms));
	return (1);
}

/*int		()
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
	printf("size: %i\n", ft_arraylen((void**)map.rooms));
	return (1);
}*/
