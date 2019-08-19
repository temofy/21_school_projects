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
	map->nbrs_rooms = -1;
	map->nbrs_links = -1;
	map->links = NULL;
	map->start = NULL;
	map->end = NULL;
	map->file = NULL;
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
	matrix = malloc(sizeof(char**) * (m + 1));
	while (i < m)
	{
		matrix[i] = ft_strnew(n);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
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
			if (j == i)
			{
				j++;
				continue;
			}
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

int		find_next_i(char **ways, int *neighbour, int vertex_i, char *checked)
{
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
	while ((*q) && (!(*q)->room || !i))
	{
		tmp = *q;
		if ((*q)->next_in_q)
			*q = (*q)->next_in_q;
		else
			*q = NULL;
		free(tmp);
		i++;
	}
}

void	record_shortest_way(char **ways, t_node2 *end)
{
	while (end->prev_room)
	{
		if (end->prev_for_bfs == -1)
		{
			ways[end->next_room[end->next_for_bfs]->i_room][end->i_room] = '2';
			end = end->next_room[end->next_for_bfs];
		}
		else
		{
			ways[end->prev_room[end->prev_for_bfs]->i_room][end->i_room] = '2';
			end = end->prev_room[end->prev_for_bfs];
		}
	}
}

t_num_q	*find_end_of_n_queue(t_num_q *q)
{
	while (q->next_in_q)
		q = q->next_in_q;
	return (q);
}

t_queue	*que_new()
{
	t_queue	*next_in_q;

	next_in_q = (t_queue*)malloc(sizeof(t_queue));
	next_in_q->next_in_q = NULL;
	next_in_q->room = NULL;
	return (next_in_q);
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


t_ps	*count_path_steps(t_map *map, char **ways, int amount_ways)
{
	int path_nbr;
	t_ps	*ps;
	int way;
	int i;
	int j;

	path_nbr = 0;
	way = 0;

	if (!(ps = (t_ps*)malloc(sizeof(t_ps) * amount_ways)))
		return (NULL);
	while (path_nbr < amount_ways)
	{
		ps[path_nbr].way_steps = 1;
		while (ways[0][way] != '2')
			way++;
		ps[path_nbr].way_begin = way;
		i = way;
		while (i != map->nbrs_rooms + 1)
		{
			ps[path_nbr].way_steps++;
			j = 0;
			while (ways[i][j] != '2')
				j++;
			i = j;
		}
		path_nbr++;
		way++;
	}
	return (ps);
}

void	rank_paths(t_ps *paths, int amount_ways)
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
			if (paths[j].way_steps > paths[j + 1].way_steps)
			{
				tmp = paths[j].way_steps;
				paths[j].way_steps = paths[j + 1].way_steps;
				paths[j + 1].way_steps = tmp;
				tmp = paths[j].way_begin;
				paths[j].way_begin = paths[j + 1].way_begin;
				paths[j + 1].way_begin = tmp;
			}
			j++;
		}
		i++;
	}
}

int 	issue_sum_prev_steps(t_ps *path, int cur_i)
{
	int sum;
	int i;

	i = cur_i - 1;
	sum = 0;
	while (i > -1)
	{
		sum += path[cur_i].way_steps - path[i].way_steps;
		i--;
	}
	return (sum);
}

t_paths *make_paths(t_ps *paths_steps, int amount_ways, char **ways, t_map *map)
{
	t_paths	*paths;
	int i;
	int	x;
	int	y;
	int k;

	i = -1;
	paths = malloc(sizeof(t_paths) * amount_ways);
	while (++i < amount_ways)
	{
		paths[i].room = malloc(sizeof(t_rooms) * paths_steps[i].way_steps);
		paths[i].amount_steps = paths_steps[i].way_steps;
		paths[i].room->i_next = paths_steps[i].way_begin;
		paths[i].room->ant_no = 0;
		k = 1;
		x = paths_steps[i].way_begin;
		while (x != map->nbrs_rooms + 1)
		{
			y = 0;
			while (ways[x][y] != '2')
				y++;
			paths[i].room[k].i_next = y;
			paths[i].room[k++].ant_no = 0;
			x = y;
		}
	}
	return (paths);
}

int 	find_last_busy_room(t_paths *paths)
{
	int i = paths->amount_steps - 1;

	while (i > -1)
	{
		if (paths->room[i].ant_no > 0)
			return (i);
		i--;
	}
	return (-1);
}

void	push_through_ants(t_map *map, int *ants_at_end, int ant, t_paths *paths)
{
	int i;

	i = find_last_busy_room(paths);
	if (i == paths->amount_steps - 2 && paths->room[i].ant_no != 0)
	{
		printf("L%i-%s ", (i < 0) ? ant : paths->room[i].ant_no, map->end->name);
		(*ants_at_end)++;
		i--;
	}
	while (i > -1)
	{
		paths->room[i + 1].ant_no = paths->room[i].ant_no;
		if (paths->room[i].ant_no != 0)
			printf("L%i-%s ", paths->room[i].ant_no, map->rooms[paths->room[i + 1].i_next - 1].name);
		i--;
	}
	if (ant != 0 && paths->amount_steps != 1)
	{
		paths->room[0].ant_no = ant;
		printf("L%i-%s ", ant, map->rooms[paths->room[0].i_next - 1].name);
	}
	else if (paths->amount_steps != 1)
		paths->room[0].ant_no = ant;
}

void	run_ant(t_map *map, int *ants_at_end, int ant, t_paths *paths)
{
	if (paths->room[0].ant_no == 0 && paths->amount_steps != 1)
	{
		printf("L%i-%s ", ant, map->rooms[paths->room[0].i_next - 1].name);
		paths->room[0].ant_no = ant;
	}
	else
		push_through_ants(map, ants_at_end, ant, paths);
}


void	launch_ants(t_map *map, char **ways, int amount_ways)
{
	int ants_at_start;
	int ant_no;
	int ants_at_end;
	int	i;
	t_ps	*paths_steps;
	t_paths	*paths;
	ant_no = 1;

	paths_steps = count_path_steps(map, ways, amount_ways);
	rank_paths(paths_steps, amount_ways);
	paths = make_paths(paths_steps, amount_ways, ways, map);

	ants_at_start = map->ants;
	ants_at_end = 0;

	while (ants_at_end != map->ants)
	{
		i = -1;
		while (++i < amount_ways)
		{
			/*if (ant_no > map->ants)
				ant_no = -1;*/
			if (ants_at_start > (issue_sum_prev_steps(paths_steps, i)))
			{    // можно попытаться оптимизировать
				run_ant(map, &ants_at_end, ant_no++, &(paths[i]));
				ants_at_start--;
			}
			else
				push_through_ants(map, &ants_at_end, 0, &(paths[i]));
		}
		printf("\n");
	}
	free(paths_steps);
	free_paths(&paths, amount_ways);
}

t_node2	*find_among_neighbors(int found_next_i, t_node2 *cur_room)
{
	int	i;
	int k;

	i = 0;
	while (i < cur_room->exits)
	{
		if (found_next_i == cur_room->next_room[i]->i_room)
		{
			k = 0;
			while (k < cur_room->next_room[i]->entrances)
			{
				if (cur_room->next_room[i]->prev_room[k]->i_room == cur_room->i_room)
					cur_room->next_room[i]->prev_for_bfs = k;
				k++;
			}
			return ((cur_room->next_room[i]));
		}
		i++;
	}
	i = 0;
	while (i < cur_room->entrances)
	{
		if (found_next_i == cur_room->prev_room[i]->i_room)
		{
			k = 0;
			while (k < cur_room->prev_room[i]->exits)
			{
				if (cur_room->prev_room[i]->next_room[k]->i_room == cur_room->i_room)
				{
					cur_room->prev_room[i]->next_for_bfs = k;
					cur_room->prev_room[i]->prev_for_bfs = -1;
				}
				k++;
			}
			return ((cur_room->prev_room[i]));
		}
		i++;
	}
	return (NULL);
}
int 	check_vertex_entry(char **ways, int vertex, t_map *map)
{
	int	i;

	i = 0;
	while(i < map->nbrs_rooms + 2)
	{
		if (ways[i][vertex] == '2')
			return (1);
		i++;
	}
	return (0);
}

int	find_neighbor_rooms(char **ways, t_map *map, t_queue **q, t_queue *first_in_q, char *checked)
{
	int		i;
	int		amount;
	int 	next_i;

	if (!first_in_q->room)
		return (-1);
	amount = count_neighbors(ways, first_in_q->room->i_room, checked, map);
	if (!amount && !first_in_q->next_in_q)
		return (-1);
	i = 0;

	next_i = 0;
	while (i < amount)
	{
		if (!(*q)->next_in_q)
		{
			(*q)->next_in_q = que_new();
			(*q) = (*q)->next_in_q;
			find_next_i(ways, &next_i, first_in_q->room->i_room, checked);
			(*q)->room = find_among_neighbors(next_i, first_in_q->room);
			if (!(*q)->room)
				checked[next_i] = '1';
			else
				checked[(*q)->room->i_room] = '1';
		}
		i++;
	}
	return (1);
}

void 	opposite_go(t_queue **q, t_queue *first_in_q, char *checked)
{
	int i;
	int k;

	i = -1;
	if (first_in_q->room->entrances == 1)
		return ;
	while (++i < first_in_q->room->entrances)
	{
		if (i != first_in_q->room->prev_for_bfs)
		{
			if (!(*q)->next_in_q)
			{
				(*q)->next_in_q = que_new();
				(*q) = (*q)->next_in_q;
				(*q)->room = first_in_q->room->prev_room[i];
				checked[(*q)->room->i_room] = '1';
				k = -1;
				while (++k < (*q)->room->exits)
					if ((*q)->room->next_room[k]->i_room == first_in_q->room->i_room)
						(*q)->room->next_for_bfs = k;
				(*q)->room->prev_for_bfs = -1;
				return;
			}
		}
	}
}

int 	bfs(t_map *map, char **ways, t_node2 *first_node, int kuku)
{
	t_queue	*q;
	t_queue *first_in_q;
	char	*checked;
	int 	i = 0;

	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);
	first_in_q = que_new();
	first_in_q->room = first_node;
	first_in_q->next_in_q = NULL;
	q = first_in_q;
	checked[q->room->i_room] = '1';
	while (first_in_q && q && i < map->nbrs_rooms + 2)
	{
		if (first_in_q->room->i_room == map->nbrs_rooms + 1)
		{
			record_shortest_way(ways, first_in_q->room);
			while (first_in_q)
				queue_pop(&first_in_q);
			free(checked);
			return (1);
		}
		if (check_vertex_entry(ways, first_in_q->room->i_room, map) == 0)
		{
			find_neighbor_rooms(ways, map, &q, first_in_q, checked);
		}
		else
		{
			opposite_go(&q, first_in_q, checked);
			find_neighbor_rooms(ways, map, &q, q, checked);
		}
		i++;
		queue_pop(&first_in_q);
	}
	free(checked);
	return (-1);
}

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
	n_queue = first;
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
				if ((ngbr != n_queue->prev_nbr && ngbr != -1))
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
			if (n_queue->nbr != map->nbrs_rooms + 1)
				checked[n_queue->nbr] = '1';
			i++;
		}
		n_queue_pop(&first);
	}
	free(checked);
	return (directed_matrix);
}

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
		rooms[i].prev_for_bfs = -1;
		rooms[i].next_for_bfs = -1;
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

int 	check_map(t_map *map, char ***ways, t_node2 **first_room)
{
	char	**directed_ways;

	if (non_repeatability_check(map) == -1)
		return (-1);
	if (check_coordinates(map) == -1)
		return (-1);
	if (make_validate_ways(map, ways) == -1)
		return (-1);
	directed_ways = set_the_direction(*ways, map);
	*first_room = create_nodes(map, directed_ways);
	ft_arrdel(&directed_ways);
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

int 	finding_non_intersecting_ways(t_map *map, char **ways, t_node2 *first_room)
{
	int i = 2;
	int 	amount_ways;
	while (bfs(map, ways, first_room, i) == 1)
	{
		//printf("%i\n", i++);
		//print_directs(ways, map);
	}
	disable_crossing_ways(ways);
	amount_ways = count_non_intersecting_ways(ways);
	if (!amount_ways)
		return (-1);
	launch_ants(map, ways, amount_ways);
	return (1);
}

int 	validate_record_run(t_map *map)
{
	int 	i;
	int 	rtn;

	char 	**ways;
	t_node2	*first_room;

	i = 0;
	first_room = NULL;
	ways = NULL;
	if (reading_ants(map->file[0], &(map->ants)) == -1)
		return (-1);
	map->nbrs_rooms = count_rooms(map->file, i + 1);
	while (map->file[++i] && ((ft_count_words(map->file[i]) == 3) || ft_isthere_chr(map->file[i], '#')))
	{
		if (record_rooms(map, map->file, &i, map->nbrs_rooms) == -1)
		{
			ft_arrdel(&map->file);
			return (-1);
		}
	}
	handler_links(map, map->file, &i);
	if (map->file[i] != NULL || !map->start || !map->end || !map->nbrs_links)
		rtn = -1;
	else
		rtn = check_map(map, &ways, &first_room);
	if (rtn == 1)
		rtn = finding_non_intersecting_ways(map, ways, first_room);
	free_rooms(&first_room, map->nbrs_rooms + 2);
	ft_arrdel(&ways);
	return (rtn);
}

int		lem_in()
{
	t_map	map;
	int 	i;

	i = 0;
	initialize_map(&map);
	map.file = (char**)malloc(sizeof(char*) * 15000);
	while (get_next_line(0, &(map.file[i++])))
	{
	}
	map.file[i - 1] = NULL;
	if(validate_record_run(&map) == -1)
		return (free_map(&map, -1));
	free_map(&map, 1);
	return (1);
}