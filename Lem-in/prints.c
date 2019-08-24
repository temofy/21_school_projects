#include "lem_in.h"

void	print_shortest_way(t_node *end, t_map *map)
{
	if (end->i_room == map->nbrs_rooms + 1)
	{
		printf("%s ", map->end->name);
		end = end->prev_room[end->prev_for_bfs];
	}
	while (end->prev_room)
	{
		printf("%s ", map->rooms[end->i_room - 1].name);
		if (end->prev_for_bfs == -1)
			end = end->next_room[end->next_for_bfs];
		else
			end = end->prev_room[end->prev_for_bfs];

	}
	printf("%s ", map->start->name);
	printf("\n");
}

void	print_matrix(char **matrix)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (matrix[i][j++])
		printf("--");
	printf("\n");
	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			printf("%c ", matrix[i][j++]);
		printf("\n");
		i++;
	}
	while (j--)
		printf("--");
	printf("\n");
}

void	print_directs(char **directions, t_map *map)
{
	int i;
	int j;
	int slash_N = 0;

	i = 0;
	while (directions[i])
	{
		j = 0;
		while (directions[i][j])
		{
			if (directions[i][j] == '2')
			{
				slash_N = 1;
				if (i == 0 && j != map->nbrs_rooms + 1)
					printf("(%s)->(%s) ", map->start->name, map->rooms[j - 1].name);
				else if (i == 0 && j == map->nbrs_rooms + 1)
					printf("(%s)->(%s) ", map->start->name, map->end->name);
				else if (i == map->nbrs_rooms + 1 && j != 0)
					printf("(%s)->(%s) ", map->end->name, map->rooms[j - 1].name);
				else if (j == 0)
					printf("(%s)->(%s) ", map->rooms[i - 1].name, map->start->name);
				else if (j == map->nbrs_rooms + 1)
					printf("(%s)->(%s) ", map->rooms[i - 1].name, map->end->name);
				else
					printf("(%s)->(%s) ", map->rooms[i - 1].name, map->rooms[j - 1].name);
			}
			j++;
		}
		if (slash_N)
		{
			printf("\n");
			slash_N = 0;
		}
		i++;
	}
}