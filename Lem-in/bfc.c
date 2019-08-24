/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:08:48 by cheller           #+#    #+#             */
/*   Updated: 2019/08/24 16:09:12 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*find_among_neighbors(int found_next_i, t_node *cur_room)
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

int		find_neighbor_rooms(t_map *m, t_queue **q, t_queue *f, char *checked)
{
	int	i;
	int	amnt;
	int	next_i;

	if (!f->room)
		return (-1);
	if (!(amnt = count_neighbors(f->room->i_room, checked, m)) && !f->next_in_q)
		return (-1);
	i = -1;
	next_i = 0;
	while (++i < amnt)
	{
		if (!(*q)->next_in_q)
		{
			(*q)->next_in_q = que_new();
			(*q) = (*q)->next_in_q;
			find_next_i(m->ways, &next_i, f->room->i_room, checked);
			(*q)->room = find_among_neighbors(next_i, f->room);
			if (!(*q)->room)
				checked[next_i] = '1';
			else
				checked[(*q)->room->i_room] = '1';
		}
	}
	return (1);
}

void	opposite_go(t_queue **q, t_queue *first, char *checked)
{
	int i;
	int k;

	i = -1;
	if (first->room->entrances == 1)
		return ;
	while (++i < first->room->entrances)
	{
		if (i != first->room->prev_for_bfs)
		{
			if (!(*q)->next_in_q)
			{
				(*q)->next_in_q = que_new();
				(*q) = (*q)->next_in_q;
				(*q)->room = first->room->prev_room[i];
				checked[(*q)->room->i_room] = '1';
				k = -1;
				while (++k < (*q)->room->exits)
					if ((*q)->room->next_room[k]->i_room == first->room->i_room)
						(*q)->room->next_for_bfs = k;
				(*q)->room->prev_for_bfs = -1;
				return ;
			}
		}
	}
}

void	reverse_walking(t_queue **q, t_queue *first, char *checked, t_map *map)
{
	opposite_go(q, first, checked);
	find_neighbor_rooms(map, q, *q, checked);
}

int		bfs(t_map *map, t_node *first_node)
{
	t_queue	*q;
	t_queue *first_in_q;
	char	*checked;
	int		i;

	i = -1;
	checked = first_init_bfc(&first_in_q, &q, first_node, map);
	while (first_in_q && q && ++i < map->nbrs_rooms + 2)
	{
		if (first_in_q->room->i_room == map->nbrs_rooms + 1)
		{
			record_shortest_way(map->ways, first_in_q->room);
			while (first_in_q)
				queue_pop(&first_in_q);
			free(checked);
			return (1);
		}
		if (check_vertex_entry(first_in_q->room->i_room, map) == 0)
			find_neighbor_rooms(map, &q, first_in_q, checked);
		else
			reverse_walking(&q, first_in_q, checked, map);
		queue_pop(&first_in_q);
	}
	free(checked);
	return (-1);
}
