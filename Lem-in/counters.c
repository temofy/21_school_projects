#include "lem_in.h"

int 	count_links(char **file, int i)
{
	int		links;

	links = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 1 && ft_isthere_chr(file[i], '-'))
			links++;
		i++;
	}
	/*if (file[i] != NULL)
		return (-1);*/
	return (links);
}

int 	count_rooms(char **file, int i)
{
	int		rooms;

	rooms = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 3 && !ft_isthere_chr(file[i], '#'))
			rooms++;
		i++;
	}
	return (rooms - 2);
}

int 	count_neighbors(char **ways, int vertex_i, char *checked, t_map *map)
{
	int neighbour;
	int amount;

	neighbour = 0;
	amount = 0;
	if (vertex_i == map->nbrs_rooms + 1)
		return (0);
	while(ways[neighbour])
	{

		if (ways[vertex_i][neighbour] == '1' && (checked[neighbour] != '1'))
			amount++;
		neighbour++;
	}
	return (amount);
}

int 	count_non_intersecting_ways(char **ways)
{
	int 	i;
	int 	amount_ways;

	i = 0;
	amount_ways = 0;
	while (ways[0][i])
	{
		if (ways[0][i] == '2')
			amount_ways++;
		i++;
	}
	return (amount_ways);
}