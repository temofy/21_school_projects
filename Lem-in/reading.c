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

	while (matrix[i])
	{
		j = 0;
		while (matrix[i][j])
			printf("%c ", matrix[i][j++]);
		printf("\n");
		i++;
	}
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
	print_matrix(*adjacency_matrix);
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

typedef struct		s_node
{
	int				i_room;
	struct s_node	*next_room;
	struct s_node	*prev_room;
}					t_node;

typedef struct		s_queue
{
	t_node			*room;
	struct s_queue	*next_in_q;
}					t_queue;

t_node	*create_node(int index, t_node *prev)
{
	t_node	*node;

	node = (t_node*)malloc(sizeof(t_node));
	node->i_room = index;
	node->next_room = NULL;
	node->prev_room = prev;
	return (node);
}

int 	count_neighbors(char **ways, int i_ver)
{
	int i;
	int amount;

	i = i_ver;
	amount = 0;
	while(ways[i])
	{
		if (ways[i][i_ver] == '1')
			amount++;
		i++;
	}
	return (amount);
}

int 	find_next_i(char **ways, int *cur_row, int col_ver)
{
	//int	i;

	//i = cur_row;
	(*cur_row)++;
	while (ways[*cur_row])
	{
		if (ways[*cur_row][col_ver] == '1')
			return (*cur_row);
		(*cur_row)++;
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

/*t_node	*find_neighbors(char **ways, t_queue *q, char *checked)
{
	t_node	*nbrs;
	int 	i;
	int 	amount;

	i = 0;
	amount = count_neighbors(ways, q->first_room->i_room);
	nbrs = (t_node*)malloc(sizeof(t_node) * amount + 1);
	while (i < amount)
	{

	}

	return (nbrs);
}*/


/*t_node	*find_neighbors(char **ways, int i_ver, t_node *prev, char *checked)
{
	t_node	*nbrs;
	int 	i;
	int 	amount;
	int 	next_i;

	i = 0;
	amount = count_neighbors(ways, i_ver);
	nbrs = (t_node*)malloc(sizeof(t_node) * amount + 1);
	next_i = 0;
	while (i < amount)
	{
		nbrs[i].i_room = find_next_i(ways, &next_i, i_ver);
		nbrs[i].next_room = NULL;
		nbrs[i].prev_room = prev;
		i++;
	}
	nbrs[i].i_room = -1;
	nbrs[i].next_room = NULL;
	nbrs[i].prev_room = NULL;
	checked[i] = 1;
	prev->next_room = nbrs;
	return (nbrs);
}*/

/*int 	check_end(t_map *map, t_queue *q)
{
	int	i;

	i = 0;
	while (q->first_room[i].i_room != -1)
	{
		if (q->first_room[i].i_room == map->nbrs_rooms + 1)
			return(i);
		i++;
	}
	return (-1);
}*/

void	record_shortest_way(char **ways, t_map *map, t_node *room, int index)
{
	int i;

	i = 0;
	//while (i < map->nbrs_rooms + 2)
	//{
	ways[room[index].i_room][room[index].prev_room->i_room] = '2';
	ways[room[index].prev_room->i_room][room[index].i_room] = '2';
	//}
}

t_node	*find_end_of_list(t_node *node)
{
	t_node *last;

	last = node;
	while (last->next_room)
		last = last->next_room;
	return (last);
}

t_queue	*find_end_of_queue(t_queue *q)
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

void	print_shortest_way(t_node *end)
{
	while (end)
	{
		printf("%i ", end->i_room);
		end = end->prev_room;
	}
	printf("\n");
}

int 	bfs(t_map *map, char **ways)
{
	t_queue	*q;
	t_queue *first_in_q;
	int 	i;
	int 	amount;
	char 	*checked;
	int next_i;

	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	ft_memset(checked, 48, map->nbrs_rooms + 2);
	first_in_q = que_new(NULL);
	first_in_q->room = create_node(0, NULL);
	q = first_in_q;

	while (q)
	{
		if (first_in_q->room->i_room == map->nbrs_rooms + 1)
		{
			print_shortest_way(first_in_q->room);
			return (1);
		}
		amount = count_neighbors(ways, first_in_q->room->i_room);
		i = 0;

		next_i = first_in_q->room->i_room;
		while (i < amount)
		{
			if (!q->next_in_q)
			{
				q->next_in_q = que_new(first_in_q);
				q = q->next_in_q;
				q->room = create_node(find_next_i(ways, &next_i, first_in_q->room->i_room), first_in_q->room);
				checked[q->room->i_room] = '1';
			}
			else
				q->next_in_q = find_end_of_queue(q);
			i++;
		}
		queue_pop(&first_in_q);
	}
	return (1);
}
/*int 	bfs(t_map *map, char **ways)
{
	int 	i;
	char 	*checked;
	int 	level;
	int		finded_way;
	t_queue	*queue;

	queue = (t_queue*)malloc(sizeof(t_queue));
	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	ft_memset(checked, 48, map->nbrs_rooms + 2);

	i = 0;

	queue->first_room = create_node(i);
	queue->next = find_end_of_list(queue->next);
	queue->next = find_neighbors(ways, i, queue->first_room, checked);
	queue_pop(queue);
	while (queue)
	{
		if ((finded_way = check_end(map, queue)) != -1)
		{
			record_shortest_way(ways, map, queue->first_room, finded_way);
			return (1);
		}
	}
	return (1);
}*/

/*int 	bfs(t_map *map, char **ways)
{
	int 	i;
	int 	*checked;
	int 	level;
	t_queue	*queue;
	queue = (t_queue*)malloc(sizeof(t_queue));
	checked = (int*)ft_memalloc(sizeof(int) * (map->nbrs_rooms + 2));
	i = 0;
	queue->first_room = create_node(i);
	checked[i] = 1;
	queue->next_room = find_neighbors(ways, i, queue->first_room);
	while (queue)
	{
	}
	return (1);
}*/

int 	check_map(t_map *map)
{
	int		rtn;
	char	**ways;

	rtn = 1;
	if (non_repeatability_check(map) == -1)
		return (-1);
	if (check_coordinates(map) == -1)
		return (-1);
	rtn = make_validate_ways(map, &ways);
	bfs(map, ways);
	print_matrix(ways);
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