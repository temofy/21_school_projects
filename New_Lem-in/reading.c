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



int 	record_links(t_map *map, char **file, int *i)
{
	char 	**values;
	static int k = 0;

	if (k == map->nbrs_links)
		return (-1);
	values = ft_strsplit(file[*i], '-'); // оптимизировать без сплита
	map->links[k].room1 = ft_strdup(values[0]);
	map->links[k].room2 = ft_strdup(values[1]);
	ft_arrdel(&values);
	k++;
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
int 	skip_comments(char **file, int *i)
{
	int		offset;

	offset = 1;
	while (file[++*i])
	{
		if (ft_isthere_chr(file[*i], '#') == 0 && ft_count_words(file[*i]) == 3)
			return (offset);
		offset++;
	}
	return (offset);
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

char	**ft_strmatrix(int m, int n)
{
	char	**matrix;
	int 	i;

	i = 0;
	if (n < 1 && m < 1)
		return (NULL);
	matrix = (char**)malloc(sizeof(char*) * m + 1);
	while (i < m)
	{
		matrix[i] = ft_strnew(n);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
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
int		find_index_room(t_map *map, char *room)
{
	int 	i;

	i = 0;
	if (ft_strcmp(map->start->name, room) == 0)
		return (i);
	i++;
	while (i - 1 < map->nbrs_rooms)
	{
		if (ft_strcmp(map->rooms[i - 1].name, room) == 0)
			return (i);
		i++;
	}
	if (ft_strcmp(map->end->name, room) == 0)
		return (i);
	return (-1);
}

int 	make_validate_ways(t_map *map, char ***adjacency_matrix)
{
	int		i;
	int 	j;
	int 	room1;
	int 	room2;

	*adjacency_matrix = ft_strmatrix(map->nbrs_rooms + 2, map->nbrs_rooms + 2);

	i = 0;
	while (i < map->nbrs_rooms + 2)
		ft_memset((*adjacency_matrix)[i++], 48, map->nbrs_rooms + 2);

	i = 0;
	while (i < map->nbrs_links)
	{
		if ((room1 = find_index_room(map, map->links[i].room1)) == -1)
			return (-1);
		if ((room2 = find_index_room(map, map->links[i].room2)) == -1)
			return (-1);
		if ((*adjacency_matrix)[room1][room2] == '1' || (*adjacency_matrix)[room2][room1] == '1')
			return (-1);
		(*adjacency_matrix)[room1][room2] = '1';
		(*adjacency_matrix)[room2][room1] = '1';
		i++;
	}
	//print_matrix(*adjacency_matrix);
	return (1);
}

int		check_coordinates(t_map *map)
{
	int i;
	int j;
	i = 0;
	while (i < map->nbrs_rooms)
	{
		j = 0;
		while (j < map->nbrs_rooms)
		{
			j = (j == i) ? j + 1 : j;
			if (map->rooms[i].x == map->rooms[j].x &&
				map->rooms[i].y == map->rooms[j].y)
				return (-1);
			j++;
		}
		if (map->rooms[i].x == map->start->x &&
			map->rooms[i].y == map->start->y)
			return (-1);
		if (map->rooms[i].x == map->end->x &&
			map->rooms[i].y == map->end->y)
			return (-1);
		i++;
	}
	return (1);
}

t_node	*create_node(int index, t_node *prev)
{
	t_node	*node;

	node = (t_node*)malloc(sizeof(t_node));
	node->i_room = index;
	node->next_room = NULL;
	node->prev_room = prev;
	return (node);
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
		if (ways[vertex_i][neighbour] == '1' && checked[neighbour] != '1')
			amount++;
		/*else if (ways[i][i_ver] == '1' && checked[i] == '1')
		{
			ways[i][i_ver] = '0';
			ways[i_ver][i] = '0';
		}*/
		neighbour++;
	}
	return (amount);
}

int 	find_next_i(char **ways, int *neighbour, int vertex_i, char *checked)
{
	//int	i;

	//i = cur_row;
	(*neighbour)++;
	while (ways[vertex_i][*neighbour])
	{
		if (ways[vertex_i][*neighbour] == '1' && checked[*neighbour] != '1')
			return (*neighbour);
		(*neighbour)++;
	}
	return (-1);

}

void	queue_pop(t_queue **q)
{
	t_queue	*tmp;
	int		i;

	i = 0;
	tmp = *q;
	if ((*q)->next_in_q)
		*q = (*q)->next_in_q;
	else
		*q = NULL;
	free(tmp);
}

void	record_shortest_way(char **ways, t_node *end)
{
	/*if (end->i_room == map->nbrs_rooms + 1)
	{
		ways[end->i_room][end->i_room] = '2';
		end = end->prev_room;
	}*/
	while (end->prev_room)
	{
		//ways[end->i_room][end->prev_room->i_room] = '2';
		ways[end->prev_room->i_room][end->i_room] = '2';
		end = end->prev_room;
	}
}

t_node	*find_end_of_list(t_node *node)
{
	t_node *last;

	last = node;
	while (last->next_room)
		last = last->next_room;
	return (last);
}

t_num_q	*find_end_of_n_queue(t_num_q *q)
{
	while (q->next_in_q)
		q = q->next_in_q;
	return (q);
}

t_queue	*que_new(t_queue *first)
{
	t_queue	*next_in_q;

	next_in_q = (t_queue*)malloc(sizeof(t_queue));
	next_in_q->next_in_q = NULL;
	next_in_q->room = NULL;
	return (next_in_q);
}

void	print_shortest_way(t_node *end, t_map *map)
{
	if (end->i_room == map->nbrs_rooms + 1)
	{
		printf("%s ", map->end->name);
		end = end->prev_room;
	}
	while (end->prev_room)
	{
		printf("%s ", map->rooms[end->i_room - 1].name);
		end = end->prev_room;
	}
	printf("%s ", map->start->name);
	printf("\n");
}

void	disable_crossing_ways(char **ways)
{
	int i;
	int j;

	i = 0;
	while (ways[i])
	{
		j = 0;
		while (ways[i][j])
		{
			if (ways[i][j] == '2' && ways[j][i] == '2')
			{
				ways[i][j] = '0';
				ways[j][i] = '0';
			}
			j++;
		}
		i++;
	}
}

int 	**count_path_steps(t_map *map, char **ways, int amount_ways)
{
	int path_nbr;
	int **paths_steps;
	int way;
	int i;
	int j;

	path_nbr = 0;
	way = 0;

	if (!(paths_steps = (int**)malloc(sizeof(int*) * amount_ways)))
		return (NULL);
	while (path_nbr < amount_ways)
	{
		paths_steps[path_nbr] = (int*)malloc(sizeof(int) * 2);
		paths_steps[path_nbr][0] = 1;
		while (ways[0][way] != '2')
			way++;
		paths_steps[path_nbr][1] = way;
		i = way;
		while (i != map->nbrs_rooms + 1)
		{
			paths_steps[path_nbr][0]++;
			j = 0;
			while (ways[i][j] != '2') // учесть когда пересекаются
				j++;
			i = j;
		}
		path_nbr++;
		way++;
	}
	return (paths_steps);
}

/*int 	*count_path_steps(t_map *map, char **ways, int amount_ways)
{
	int path_nbr;
	int *paths_steps;
	int way;
	int i;
	int j;

	path_nbr = 0;
	way = 0;
	if (!(paths_steps = (int*)malloc(sizeof(int) * amount_ways)))
		return (NULL);
	while (path_nbr < amount_ways)
	{
		paths_steps[path_nbr] = 1;
		while (ways[0][way] != '2')
			way++;
		i = way;
		while (i != map->nbrs_rooms + 1)
		{
			paths_steps[path_nbr]++;
			j = 0;
			while (ways[i][j] != '2') // учесть когда пересекаются
				j++;
			i = j;
		}
		path_nbr++;

	}
	return (paths_steps);
}*/

void	rank_paths(int **paths, int amount_ways)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < amount_ways)
	{
		j = 0;
		while (j < amount_ways - 1)
		{
			if (paths[j][0] > paths[j + 1][0])
			{
				tmp = paths[j][0];
				paths[j][0] = paths[j + 1][0];
				paths[j + 1][0] = tmp;
				tmp = paths[j][1];
				paths[j][1] = paths[j + 1][1];
				paths[j + 1][1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int 	issue_sum_prev_steps(int **path, int cur_i)
{
	int sum;
	int i;

	i = cur_i - 1;
	sum = 0;
	while (i > -1)
	{
		sum += path[cur_i][0] - path[i][0];
		i--;
	}
	return (sum);
}

t_paths *make_paths(int **paths_steps, int amount_ways, char **ways, t_map *map)
{
	t_paths	*paths;
	int i;
	int	x;
	int	y;
	int k;

	i = -1;
	paths = (t_paths*)malloc(sizeof(t_paths) * amount_ways);
	while (++i < amount_ways)
	{
		k = -1;
		paths[i].room = (int**)malloc(sizeof(int*) * paths_steps[i][0]);
		while (++k < paths_steps[i][0])
			paths[i].room[k] = (int*)malloc(sizeof(int) * 2);
		paths[i].amount_steps = paths_steps[i][0];
		paths[i].room[0][0] = paths_steps[i][1];
		paths[i].room[0][1] = 0;
		k = 1;
		x = paths_steps[i][1];
		while (x != map->nbrs_rooms + 1)
		{
			y = 0;
			while (ways[x][y] != '2')
				y++;
			paths[i].room[k][0] = y;
			paths[i].room[k++][1] = 0;
			x = y;
		}
	}
	return (paths);
}

/*int 	**make_paths(int **paths_steps, int amount_ways, char **ways, t_map *map)
{
	int	**paths;
	int i;
	int	x;
	int	y;
	int k;

	i = -1;
	paths = (int**)malloc(sizeof(int*) * amount_ways);
	while (++i < amount_ways)
	{
		paths[i] = (int *) malloc(sizeof(int) * paths_steps[i][0] + 1);
		paths[i][0] = paths_steps[i][0];
		paths[i][1] = paths_steps[i][1];
		k = 2;
		x = paths_steps[i][1];
		while (x != map->nbrs_rooms + 1)
		{
			y = 0;
			while (ways[x][y] != '2')
				y++;
			paths[i][k] = y;
			x = y;
		}
	}
	return (paths);
}*/

int 	find_last_busy_room(t_paths *paths)
{
	int i = 0;

	while (i < paths->amount_steps)
	{
		//paths->room[i][1] > 0;
		i++;
	}
	return (i);
}

void	run_ant(t_map *map, int *ants_at_end, int ant, t_paths *paths)
{
	int	i;
	int tmp;

	if (paths->room[0][1] == 0 && paths->amount_steps != 1)
	{
		printf("L%i-%s ", ant, map->rooms[paths->room[0][0] - 1].name);
		paths->room[0][1] = ant;
	}
	//*ants_at_end = map->ants;
	else
	{
		i = find_last_busy_room(paths);
		if (i == paths->amount_steps - 2)
		{
			printf("L%i-%s ", paths->room[i--][1], map->end->name);
			(*ants_at_end)++;
		}
		while (i > 0)
		{
			paths->room[i][1] = paths->room[i - 1][1];
			printf("L%i-%s ", paths->room[i][1], map->rooms[paths->room[i][0] - 1].name);
			i--;
		} //учесть когда нет поступления мурьвев, но надо провдинуть до конца
	}
}


void	launch_ants(t_map *map, char **ways, int amount_ways)
{
	int ants_at_start;
	int ant_no;
	int ants_at_end;
	int	i;
	int **paths_steps;
	t_paths	*paths;
	int steps_acroos_sw;
	ant_no = 1;

	steps_acroos_sw = map->ants + map->shortest_steps - 1;
	paths_steps = count_path_steps(map, ways, amount_ways);
	paths = make_paths(paths_steps, amount_ways, ways, map);

	ants_at_start = map->ants;
	ants_at_end = 0;
	rank_paths(paths_steps, amount_ways);

	i = -1;
	while (++i < amount_ways)
		printf("%i'steps: %i\n", i, paths_steps[i][0]);
	i = -1;
	while (ants_at_end != map->ants)
	{
		while (++i < amount_ways)
		{
			if (ants_at_start > (issue_sum_prev_steps(paths_steps, i))) // можно попытаться оптимизировать
				run_ant(map, &ants_at_end, ant_no++, &(paths[i]));
		}
		printf("\n");
	}
	//printf("L%i-%s");
}

int 	check_created_room(char *created_room, int room_index)
{
	if (created_room[room_index] == '1')
		return (1);
	else
		return (0);
}

t_node	*finding_room(char **ways, t_node *first, int needed_room)
{
	return (NULL);
}

int 	bfs(t_map *map, char **ways, t_node2 *first_node, char *created_room)
{
	t_queue	*q;
	t_queue *first_in_q;
	int		i;
	int		amount;
	char	*checked;
	int 	next_i;

	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	ft_memset(checked, 48, map->nbrs_rooms + 2);

	first_in_q->room = first_node;
	first_in_q->next_in_q = NULL;
	q = first_in_q;
	checked[q->room->i_room] = '1';

	while (first_in_q && q)
	{
		if (first_in_q->room->i_room == map->nbrs_rooms + 1)
		{
			//print_shortest_way(first_in_q->room, map);
			//record_shortest_way(ways, first_in_q->room);
			return (1);
		}
		amount = count_neighbors(ways, first_in_q->room->i_room, checked, map);
		if (!amount && !first_in_q->next_in_q)
			return (-1);
		i = 0;

		//next_i = 0;
		while (i < amount)
		{
			if (!q->next_in_q)
			{
				q->next_in_q = que_new(first_in_q);
				q = q->next_in_q;
				//int found_next_i = find_next_i(ways, &next_i, first_in_q->room->i_room, checked);
				q->room = first_in_q->room->next_room[i];
				checked[q->room->i_room] = '1';
		}
		i++;
	}
	queue_pop(&first_in_q);
}
}
/*int 	bfs(t_map *map, char **ways, t_node *first_node, char *created_room) // последняя конфигурция
{
t_queue	*q;
t_queue *first_in_q;
int 	i;
int 	amount;
char 	*checked;
int 	next_i;

checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
ft_memset(checked, 48, map->nbrs_rooms + 2);
first_in_q = que_new(NULL);
if (!first_node)
{
	first_in_q->room = create_node(0, NULL);
	created_room = ft_strnew(map->nbrs_rooms + 2);
	ft_memset(created_room, 48, map->nbrs_rooms +2);
	created_room[0] = '1';
}
q = first_in_q;
checked[q->room->i_room] = '1';

while (first_in_q && q)
{
	if (first_in_q->room->i_room == map->nbrs_rooms + 1)
	{
		print_shortest_way(first_in_q->room, map);
		record_shortest_way(ways, first_in_q->room);
		return (1);
	}
	amount = count_neighbors(ways, first_in_q->room->i_room, checked, map);
	//if (amount && first_in_q->room->next_room) заморожено

	if (!amount && !first_in_q->next_in_q)
		return (-1);
	i = 0;

	next_i = 0;
	while (i < amount)
	{
		if (!q->next_in_q)
		{
			q->next_in_q = que_new(first_in_q);
			q = q->next_in_q;


			int found_next_i = find_next_i(ways, &next_i, first_in_q->room->i_room, checked);
			/*if (check_created_room(created_room, found_next_i) != 1 &&
				check_created_room(created_room, first_in_q->room->i_room))*/
					/*finding_room();
				else*/
					/*q->room = create_node(found_next_i, first_in_q->room);
				checked[q->room->i_room] = '1';


			}
			i++;
		}
		queue_pop(&first_in_q);
	}
	return (1);
} */

/*int 	bfs(t_map *map, char **ways, t_node *first_node)
{
	t_queue	*q;
	t_queue *first_in_q;
	int 	i;
	int 	amount;
	char 	*checked;
	int 	next_i;

	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	ft_memset(checked, 48, map->nbrs_rooms + 2);
	first_in_q = que_new(NULL);
	if (!first_node)
		first_in_q->room = create_node(0, NULL);
	q = first_in_q;
	checked[q->room->i_room] = '1';

	while (first_in_q && q)
	{
		if (first_in_q->room->i_room == map->nbrs_rooms + 1)
		{
			print_shortest_way(first_in_q->room, map);
			record_shortest_way(ways, first_in_q->room);
			return (1);
		}
		amount = count_neighbors(ways, first_in_q->room->i_room, checked);
		if (!amount && !first_in_q->next_in_q)
			return (-1);
		i = 0;

		next_i = 0;
		while (i < amount)
		{
			if (!q->next_in_q)
			{
				q->next_in_q = que_new(first_in_q);
				q = q->next_in_q;
				q->room = create_node(find_next_i(ways, &next_i, first_in_q->room->i_room, checked), first_in_q->room);
				checked[q->room->i_room] = '1';
			}
			i++;
		}
		queue_pop(&first_in_q);
	}
	return (1);
}*/

int		count_all_neighbors(char **ways, int vertex_i)
{
	int neighbour;
	int amount;

	neighbour = 0;
	amount = 0;
	while(ways[neighbour])
	{
		if (ways[vertex_i][neighbour] == '1')
			amount++;
		neighbour++;
	}
	return (amount);
}

int 	find_created_room(char **ways, int *neighbour, int vertex_i, char *checked)
{
	(*neighbour)++;
	while (ways[vertex_i][*neighbour])
	{
		if (ways[vertex_i][*neighbour] == '1' && checked[*neighbour] == '1')
			return (*neighbour);
		(*neighbour)++;
	}
	return (-1);

}

void	*create_full_chain_nodes(char **ways, t_node *cur_room, t_node *first, char *checked)
{
	int 	amount_ngbrs;
	int 	i;
	int 	next_neighbor;

	amount_ngbrs = count_all_neighbors(ways, cur_room->i_room);
	cur_room->next_room = (t_node *) malloc(sizeof(t_node) * amount_ngbrs);
	next_neighbor = 0;
	i = 0;
	while (i < amount_ngbrs)
	{
		cur_room->next_room[i].i_room = find_next_i(ways, &next_neighbor, cur_room->i_room, checked);
		cur_room->next_room[i].prev_room = cur_room;
		cur_room->next_room[i].next_room = create_full_chain_nodes(ways, &(cur_room->next_room[i]), first, checked);
		checked[cur_room->next_room[i].i_room] = '1';
		i++;
	}
	return (NULL);
}

/*t_node	*create_nodes(t_map *map, char **ways)
{
	t_node	*first;
	t_node	*cur_room;
	char 	*checked;
	int 	amount_ngbrs;
	int 	i;
	int 	next_neighbor;

	checked = ft_strnew(map->nbrs_rooms + 2);
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);
	first = create_node(0 , NULL);
	checked[0] = '1';
	cur_room = first;
	amount_ngbrs = count_neighbors(ways, cur_room->i_room, checked);
	i = 0;
	while (i < amount_ngbrs)
	{
		cur_room->next_room[i].i_room = find_next_i(ways, &next_neighbor, cur_room->i_room, checked);
		cur_room->next_room[i].prev_room = cur_room;
		create_full_chain_nodes(ways, &(cur_room->next_room[i]), first, checked);
		checked[cur_room->next_room[i].i_room] = '1';
		i++;
	}*/
	//while (cur_room)
	//{
		/*amount_ngbrs = count_neighbors(ways, cur_room->i_room, checked);
		cur_room->next_room = (t_node *) malloc(sizeof(t_node) * amount_ngbrs);
		next_neighbor = 0;
		i = 0;
		while (i < amount_ngbrs)
		{
			cur_room->next_room[i].i_room = find_next_i(ways, &next_neighbor, cur_room->i_room, checked);
			cur_room->next_room[i].prev_room = cur_room;
			cur_room->next_room[i].next_room = create_full_chain_nodes(ways, &(cur_room->next_room[i]), first, checked);
			checked[cur_room->next_room[i].i_room] = '1';
			i++;
		}*/
	//}
//	return (first);
//}

int 	find_next_without_check(char **ways, int *neighbour, int vertex_i)
{
	(*neighbour)++;
	while (ways[vertex_i][*neighbour])
	{
		if (ways[vertex_i][*neighbour] == '1')
			return (*neighbour);
		(*neighbour)++;
	}
	return (-1);
}

t_num_q	*n_que_new()
{
	t_num_q	*next_in_q;

	next_in_q = (t_num_q*)malloc(sizeof(t_num_q));
	next_in_q->next_in_q = NULL;
	next_in_q->nbr = -1;
	return (next_in_q);
}
void	n_queue_pop(t_num_q **q)
{
	t_num_q	*tmp;

	tmp = *q;
	if ((*q)->next_in_q)
		*q = (*q)->next_in_q;
	else
		*q = NULL;
	free(tmp);
}

int 	find_in_n_queue(t_num_q *first, int room, int lvl)
{
	while (first)
	{
		if (first->nbr == room && first->layer_lvl >= lvl)
			return (1);
		else if (first->nbr == room)
			return (-1);
		first = first->next_in_q;
	}
	return (-1);
}

char	**set_the_direction(char **ways, t_map *map)
{
	char	*checked;
	char	**directed_matrix;
	int 	i;
	int 	next_i;
	int 	amount;
	t_num_q	*first;
	t_num_q	*n_queue;

	checked = ft_strnew(map->nbrs_rooms + 2);
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);

	i = -1;
	directed_matrix = ft_strmatrix(map->nbrs_rooms + 2, map->nbrs_rooms + 2);
	while (directed_matrix[++i])
		directed_matrix[i] = ft_memset(directed_matrix[i], 48, map->nbrs_rooms + 2);

	first = n_que_new();
	first->nbr = 0;
	first->prev_nbr = -1;
	first->layer_lvl = 0;
	checked[0] = '1';
	while(n_queue && first)
	{
		n_queue = first;
		amount = count_neighbors(ways, n_queue->nbr, checked, map);
		next_i = 0;
		if ((!amount && n_queue->nbr != map->nbrs_rooms + 1)) // учесть когда есть команты, но они созданы уже, и это не предыдущая
		{
			while (next_i != map->nbrs_rooms + 2)
			{
				int ngbr = find_next_without_check(ways, &next_i, n_queue->nbr);
				if ((ngbr != n_queue->prev_nbr && ngbr != -1)/* ||
						(find_in_n_queue(first, ngbr, n_queue->layer_lvl) == 1 || ngbr == map->nbrs_rooms + 1)*/)
					directed_matrix[n_queue->nbr][ngbr] = '1';
			}
				n_queue = n_queue->next_in_q;
		}
		i = 0;

		while (i < amount)
		{
			find_end_of_n_queue(n_queue)->next_in_q = n_que_new();
			n_queue = find_end_of_n_queue(n_queue);
			n_queue->prev_nbr = first->nbr;
			n_queue->nbr = find_next_i(ways, &next_i, first->nbr, checked);
			n_queue->layer_lvl = first->layer_lvl + 1;
			directed_matrix[first->nbr][n_queue->nbr] = '1';
			checked[n_queue->nbr] = '1';
			i++;
		}
		n_queue_pop(&first);
	}
	return (directed_matrix);
}
/*char	**set_the_direction(char **ways, t_map *map)
{
	char	*checked;
	char	**directed_matrix;
	int 	i;
	int 	next_i;
	int 	amount;
	t_num_q	*first;
	t_num_q	*n_queue;

	checked = ft_strnew(map->nbrs_rooms + 2);
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);

	i = -1;
	directed_matrix = ft_strmatrix(map->nbrs_rooms + 2, map->nbrs_rooms + 2);
	while (directed_matrix[++i])
		directed_matrix[i] = ft_memset(directed_matrix[i], 48, map->nbrs_rooms + 2);

	first = n_que_new();
	first->nbr = 0;
	first->layer_lvl = 0;
	checked[0] = '1';
	while(n_queue && first)
	{
		n_queue = first;
		amount = exitsneighbors(ways, n_queue->nbr, checked, map);
		next_i = 0;
		if (!amount && n_queue->nbr != map->nbrs_rooms + 1)
		{
			while (next_i != map->nbrs_rooms + 2)
			{
				int ngbr = find_next_without_check(ways, &next_i, n_queue->nbr);
				if (find_in_n_queue(first, ngbr, n_queue->layer_lvl) == 1 || ngbr == map->nbrs_rooms + 1)
					directed_matrix[n_queue->nbr][ngbr] = '1';
			}
			n_queue = n_queue->next_in_q;
		}
		i = 0;

		while (i < amount)
		{
			find_end_of_n_queue(n_queue)->next_in_q = n_que_new();
			n_queue = find_end_of_n_queue(n_queue);
			n_queue->nbr = find_next_i(ways, &next_i, first->nbr, checked);
			n_queue->layer_lvl = first->layer_lvl + 1;
			directed_matrix[first->nbr][n_queue->nbr] = '1';
			checked[n_queue->nbr] = '1';
			i++;
		}
		n_queue_pop(&first);
	}
	return (directed_matrix);
}*/

int     exitsamount_entrances(char **directions, int room, int size)
{
	int i;
	int entrances;

	i = 0;
	entrances = 0;
	while (i < size)
	{
		if (directions[i++][room] == '1')
			entrances++;
	}
	return (entrances);
}

int     exitsamount_exits(char **directions, int room)
{
	int j;
	int exits;

	j = 0;
	exits = 0;
	while (directions[room][j])
	{
		if (directions[room][j++] == '1')
			exits++;
	}
	return (exits);
}

/*void	assign_next_rooms(t_node *rooms, t_node *cur_room, char **dir)
{
	int	assigments;
	int j;

	j = 0;
	assigments = 0;
	if (cur_room->exits == 0)
		cur_room->next_room = NULL;
	while (assigments < cur_room->exits)
	{
		while (dir[cur_room->i_room][j])
		{
			if (dir[cur_room->i_room][j] == '1')
				cur_room->next_room[assigments++] = rooms[j];
			j++;
		}
		assigments++;
	}
}

void	assign_prev_rooms(t_node *rooms, t_node *cur_room, char **dir, int size)
{
	int	assigments;
	int i;

	i = 0;
	assigments = 0;
	if (cur_room->entrances == 0)
		cur_room->prev_room = NULL;
	while (assigments < cur_room->entrances)
	{
		while (i < size)
		{
			if (dir[i][cur_room->i_room] == '1')
				cur_room->prev_room[assigments++] = rooms[i];
			i++;
		}
	}
}*/

void	assign_next_rooms(t_node2 *rooms, t_node2 *cur_room, char **dir)
{
	int	assigments;
	int j;

	j = 0;
	assigments = 0;
	if (cur_room->exits != 0)
	{
		while (dir[cur_room->i_room][j])
		{
			if (dir[cur_room->i_room][j] == '1') {
				cur_room->next_room[assigments] = &rooms[j];

				assigments++;
			}
			j++;
		}
	}
}

void	assign_prev_rooms(t_node2 *rooms, t_node2 *cur_room, char **dir, int size)
{
	int	assigments;
	int i;

	i = 0;
	assigments = 0;
	if (cur_room->entrances != 0)
	{
		while (i < size) {
			if (dir[i][cur_room->i_room] == '1') {
				cur_room->prev_room[assigments] = &rooms[i];
				assigments++;
			}
			i++;
		}
	}
}


t_node2	*create_nodes(t_map *map, char **directions) // и сразу проверить на удаляемость
{
	t_node2	*rooms;
	int		i;

	i = 0;
	rooms = (t_node2*)malloc(sizeof(t_node2) * (map->nbrs_rooms + 2));
	while (i < map->nbrs_rooms + 2)
	{

		rooms[i].i_room = i;
		rooms[i].exits = exitsamount_exits(directions, i);
		rooms[i].next_room = (rooms[i].exits == 0) ? NULL : (t_node2**)malloc(sizeof(t_node2*) * rooms[i].exits);
		assign_next_rooms(rooms, &(rooms[i]), directions);
		rooms[i].entrances = exitsamount_entrances(directions, i, map->nbrs_rooms + 2);
		rooms[i].prev_room = (rooms[i].entrances == 0) ? NULL : (t_node2**)malloc(sizeof(t_node2*) * rooms[i].entrances);
		assign_prev_rooms(rooms, &(rooms[i]), directions, map->nbrs_rooms + 2);
		i++;
	}
	return (rooms);
}

/*t_node	*create_nodes(t_map *map, char **ways, char **directions) // и сразу проверить на удаляемость
{
	t_node	*rooms;
	int		i;

	i = 0;
	rooms = (t_node*)malloc(sizeof(t_node) * map->nbrs_rooms + 2);
	while (i < map->nbrs_rooms + 2)
	{
		rooms[i].i_room = i;
		rooms[i].exits = count_amount_exits(directions, i);
		rooms[i].next_room = (rooms[i].exits == 0) ? NULL : (t_node*)malloc(sizeof(t_node) * rooms[i].exits);
		assign_next_rooms(rooms, &(rooms[i]), directions);
		rooms[i].entrances = count_amount_entrances(directions, i, map->nbrs_rooms + 2);
		rooms[i].prev_room = (rooms[i].entrances == 0) ? NULL : (t_node*)malloc(sizeof(t_node) * rooms[i].entrances);
		assign_prev_rooms(rooms, &(rooms[i]), directions, map->nbrs_rooms + 2);
		i++;
	}
	return (rooms);
}*/

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

void	print_directs(char **directions, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (directions[i])
	{
		j = 0;
		while (directions[i][j])
		{
			if (directions[i][j] == '1')
			{
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
		printf("\n");
		i++;
	}
}

int 	count_way_step(t_map *map, char **ways, int start)
{
	int	steps;
	int	j;

	steps = 1;

	while (start != map->nbrs_rooms + 1)
	{
		steps++;
		j = 0;
		while (ways[start][j] != '2') // учесть когда пересекаются
			j++;
		start = j;
	}
	return (steps);
}
int 	*make_shortest_way(t_map *map, char **ways)
{
	int *shortest_way;
	int steps;
	int i;
	int j;
	int k;

	i = 0;
	while (ways[0][i] != '2')
		i++;
	steps = count_way_step(map, ways, i);
	map->shortest_steps = steps;
	if (!(shortest_way = (int*)malloc(sizeof(int) * steps)))
		return (NULL);
	shortest_way[0] = 0;
	shortest_way[1] = i;
	k = 2;
	while (i != map->nbrs_rooms + 1)
	{
		j = 0;
		while (ways[i][j] != '2')
			j++;
		i = j;
		shortest_way[k++] = i;
	}
	return (shortest_way);
}

void	disable_nonsensical_directions(char **directions)
{
	int i;
	int j;

	i = 0;
	while (directions[i])
	{
		j = 0;
		while (directions[i][j])
		{
			if (directions[i][j] == '1' && directions[j][i] == '1')
			{
				directions[i][j] = '0';
				directions[j][i] = '0';
			}
			j++;
		}
		i++;
	}
}

int 	check_map(t_map *map)
{
	int		rtn;
	char	**ways;
	char	**directed_ways;
	//int 	amount_ways;
	//char 	*created_paths;
	t_node2	*first_room;

	first_room = NULL;
	rtn = 1;
	if (non_repeatability_check(map) == -1)
		return (-1);
	if (check_coordinates(map) == -1)
		return (-1);
	rtn = make_validate_ways(map, &ways);
	print_matrix(ways);
	directed_ways = set_the_direction(ways, map); // учесть то, что где-то наклдывается
	print_matrix(directed_ways);
	print_directs(directed_ways, map);
	// проверка на незаконченность
	//print_matrix(ways);
	disable_nonsensical_directions(directed_ways); //допилить, чтобы отрезало полностью
	first_room = create_nodes(map, directed_ways);

	//if (bfs(map, ways, first_room, created_paths) == -1)
	//	return (-1); // заменить

	/*map->shortest_way = make_shortest_way(map, ways);
	while (bfs(map, ways, first_room, created_paths) == 1)
		print_matrix(ways);
	printf("Путей не найдено больше!\n");
	disable_crossing_ways(ways);
	disable_crossing_ways(ways);
	print_matrix(ways);
	amount_ways = count_non_intersecting_ways(ways);
	print_directs(ways, map);
	//launch_ants(map, ways, amount_ways);
	//print_matrix(ways);
	printf("Количество непересекающихся путей: %i\n", amount_ways);*/
	return (rtn);
}

int 	handler_links(t_map *map, char **file, int *i)
{
	map->nbrs_links = count_links(file, *i);
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
	return (1);
}