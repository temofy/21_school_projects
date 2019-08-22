#include "lem_in.h"

int 	record_links(t_map *map, char **file, int *i)
{
	char 	**values;
	static int k = 0;

	if (k == map->nbrs_links)
		return (-1);
	//values = ft_strsplit(file[*i], '-'); // оптимизировать без сплита
	//map->links[k].room1 = ft_strdup(values[0]);
	//map->links[k].room2 = ft_strdup(values[1]);
	map->links[k].room1 = links_split(file[*i], 1);
	map->links[k].room2 = links_split(file[*i], 2);
	//ft_arrdel(&values);
	k++;
	return (1);
}

int 	record_rooms(t_map *map, char **file, int *i, int amount)
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
			while (++j < amount) {
				map->rooms[j].x = -1;
				map->rooms[j].y = -1;
			}
		}
		if (reading_rooms(file[*i], map) == -1)
			return(-1);
	}
	return (1);
}

int 	handler_hashes(t_map *map, char **file, int *i)
{
	if (ft_strcmp("##start", file[*i]) == 0 && !(map->start))
	{
		if (reading_se(file[*i + skip_comments(file, i)], &(map->start)) == -1)
			return (-1);
		return (1);
	}
	else if (ft_strcmp("##start", file[*i]) == 0 && map->start)
		return (-1);
	else if (ft_strcmp("##end", file[*i]) == 0 && !(map->end))
	{
		if (reading_se(file[*i + skip_comments(file, i)], &(map->end)) == -1)
			return (-1);
		return (1);
	}
	else if (ft_strcmp("##end", file[*i]) == 0 && map->end)
		return (-1);
	return (1);
}

int 	handler_links(t_map *map, char **file, int *i)
{
	map->nbrs_links = count_links(file, *i);
	if (!map->nbrs_rooms)
		return (-1);
	while (file[*i] && (((ft_count_words(file[*i]) == 1) && ft_isthere_chr(file[*i], '-')) || ft_isthere_chr(file[*i], '#')))
	{
		if (file[*i][0] == '#')
		{
			if (handler_hashes(map, file, i) == -1)
				return (-1);
		}
		else
		{
			if (!map->links)
				map->links = (t_links *) ft_memalloc(sizeof(t_links) * map->nbrs_links);
			if (record_links(map, file, i) == -1)
				return (-1);
		}
		(*i)++;
	}
	return (1);
}