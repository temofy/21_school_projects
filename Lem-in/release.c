#include "lem-in.h"

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
