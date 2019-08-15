#include "lem-in.h"

int 	free_map(t_map *map, int status)
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
		free(map->links);
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
	map->rooms = NULL;
	map->links = NULL;
	map->start = NULL;
	map->end = NULL;
	return (status);
}
