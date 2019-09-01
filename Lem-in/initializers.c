/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:46:56 by cheller           #+#    #+#             */
/*   Updated: 2019/08/25 12:47:04 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	map->paths = NULL;
	map->amount_ways = -1;
	map->ways = NULL;
}

void	initilize_objects(char ***directed_matrix, t_num_q **first, t_map *map)
{
	int	i;

	i = -1;
	*directed_matrix = ft_strmatrix(map->nbrs_rooms + 2, map->nbrs_rooms + 2);
	while ((*directed_matrix)[++i])
		(*directed_matrix)[i] =
				ft_memset((*directed_matrix)[i], 48, map->nbrs_rooms + 2);
	*first = n_que_new();
	(*first)->nbr = 0;
	(*first)->prev_nbr = -1;
	(*first)->layer_lvl = 0;
}

void	initialize_path(t_paths *paths, int i, t_ps *paths_steps)
{
	paths[i].amount_steps = paths_steps[i].way_steps;
	paths[i].room->i_next = paths_steps[i].way_begin;
	paths[i].room->ant_no = 0;
}

char	*first_init_bfc(t_queue **first, t_queue **q, t_node *node, t_map *map)
{
	char	*checked;

	*first = que_new();
	(*first)->room = node;
	(*first)->next_in_q = NULL;
	*q = *first;
	checked = (char*)ft_memalloc((map->nbrs_rooms + 3));
	checked = ft_memset(checked, 48, map->nbrs_rooms + 2);
	checked[(*q)->room->i_room] = '1';
	return (checked);
}
