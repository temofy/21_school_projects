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

#include "lem_in.h"

int		reading_ants(char *string, int *ants)
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
	if (!*ants)
		return (-1);
	return (1);
}

char	*links_split(char *str, int room, int seperator)
{
	int		j;
	int		len;
	char	*room1;
	char	*room2;

	j = -1;
	len = 0;
	while (str[++j])
	{
		if (str[j] == '-' && !seperator)
		{
			room1 = ft_strnew(len);
			room1 = ft_memcpy(room1, str, len);
			if (room == 1)
				return (room1);
			seperator = 1;
			len = 0;
			continue;
		}
		len++;
	}
	room2 = ft_strnew(len);
	room2 = ft_memcpy(room2, str + ft_strlen(room1) + 1, len);
	free(room1);
	return (room2);
}

void	appropriation_neighbors(t_map *map, t_sq *sq, char **directed_matrix, char *checked)
{
	int	amount;
	int	next_i;
	int	i;
	int	ngbr;

	*sq->nq = (*sq->first);
	amount = count_neighbors((*sq->nq)->nbr, checked, map);
	next_i = 0;
	if ((!amount && (*sq->nq)->nbr != map->nbrs_rooms + 1))
	{
		while (next_i != map->nbrs_rooms + 2)
		{
			ngbr = find_next_without_check(map->ways, &next_i, (*sq->nq)->nbr);
			if ((ngbr != (*sq->nq)->prev_nbr && ngbr != -1))
				directed_matrix[(*sq->nq)->nbr][ngbr] = '1';
		}
		*sq->nq = (*sq->nq)->next_in_q;
	}
	i = 0;
	while (i < amount)
	{
		find_end_of_n_queue(*sq->nq)->next_in_q = n_que_new();
		*sq->nq = find_end_of_n_queue(*sq->nq);
		(*sq->nq)->prev_nbr = (*sq->first)->nbr;
		(*sq->nq)->nbr = find_next_i(map->ways, &next_i, (*sq->first)->nbr, checked);
		(*sq->nq)->layer_lvl = (*sq->first)->layer_lvl + 1;
		directed_matrix[(*sq->first)->nbr][(*sq->nq)->nbr] = '1';
		if ((*sq->nq)->nbr != map->nbrs_rooms + 1)
			checked[(*sq->nq)->nbr] = '1';
		i++;
	}
}

char	**set_the_direction(t_map *map)
{
	char	*checked;
	char	**dir_matrix;
	t_num_q	*first;
	t_num_q	*n_queue;
	t_sq	sq;

	checked = ft_strnew(map->nbrs_rooms + 2);
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);
	initilize_objects(&dir_matrix, &first, map);
	checked[0] = '1';
	n_queue = first;
	while (n_queue && first)
	{
		sq.first = &first;
		sq.nq = &n_queue;
		appropriation_neighbors(map, &sq, dir_matrix, checked);
		n_queue_pop(&first);
	}
	free(checked);
	return (dir_matrix);
}

t_node	*create_nodes(t_map *map, char **directions)
{
	t_node	*rooms;
	int		i;

	i = 0;
	rooms = (t_node*)malloc(sizeof(t_node) * (map->nbrs_rooms + 2));
	while (i < map->nbrs_rooms + 2)
	{
		rooms[i].i_room = i;
		rooms[i].prev_for_bfs = -1;
		rooms[i].next_for_bfs = -1;
		rooms[i].exits = exitsamount_exits(directions, i);
		rooms[i].next_room = (rooms[i].exits == 0) ? NULL : (t_node**)
				malloc(sizeof(t_node*) * rooms[i].exits);
		assign_next_rooms(rooms, &(rooms[i]), directions);
		rooms[i].entrances = exitsamount_entrances(directions, i, map->nbrs_rooms + 2);
		rooms[i].prev_room = (rooms[i].entrances == 0) ? NULL : (t_node**)
				malloc(sizeof(t_node*) * rooms[i].entrances);
		assign_prev_rooms(rooms, &(rooms[i]), directions, map->nbrs_rooms + 2);
		i++;
	}
	return (rooms);
}
