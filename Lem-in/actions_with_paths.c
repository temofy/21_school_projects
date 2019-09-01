/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_with_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 21:02:52 by cheller           #+#    #+#             */
/*   Updated: 2019/08/23 21:02:55 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		counter_addition(t_map *map, int i)
{
	int	j;

	j = 0;
	while ((map->ways)[i][j] != '2')
		j++;
	return (j);
}

t_ps	*count_path_steps(t_map *map, int amount_ways)
{
	int		path_nbr;
	t_ps	*ps;
	int		way;
	int		i;

	path_nbr = -1;
	way = 0;
	if (!(ps = (t_ps*)malloc(sizeof(t_ps) * amount_ways)))
		return (NULL);
	while (++path_nbr < amount_ways)
	{
		ps[path_nbr].way_steps = 1;
		while ((map->ways)[0][way] != '2')
			way++;
		ps[path_nbr].way_begin = way;
		i = way;
		while (i != map->nbrs_rooms + 1)
		{
			ps[path_nbr].way_steps++;
			i = counter_addition(map, i);
		}
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

int		issue_sum_prev_steps(t_ps *path, int cur_i)
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

t_paths	*make_paths(t_ps *paths_steps, int amount_ways, char **ways, t_map *map)
{
	t_paths	*paths;
	int		i;
	int		x;
	int		y;
	int		k;

	i = -1;
	paths = malloc(sizeof(t_paths) * amount_ways);
	while (++i < amount_ways)
	{
		paths[i].room = malloc(sizeof(t_rooms) * paths_steps[i].way_steps);
		initialize_path(paths, i, paths_steps);
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
