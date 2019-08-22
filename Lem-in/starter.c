/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:03:39 by cheller           #+#    #+#             */
/*   Updated: 2019/08/22 19:03:45 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ant_turn(int ant, char *next_room)
{
	int		nbr_size;
	int		str_len;
	char	*str_nbr;

	nbr_size = nbr_len(ant);
	str_len = ft_strlen(next_room);
	str_nbr = ft_itoa(ant);
	write(1, "L", 1);
	write(1, str_nbr, nbr_size);
	write(1, "-", 1);
	write(1, next_room, str_len);
	write(1, " ", 1);
	free(str_nbr);
}

void	push_through_ants(t_map *map, int *ants_at_end, int ant, t_paths *paths)
{
	int i;

	i = find_last_busy_room(paths);
	if (i == paths->amount_steps - 2 && paths->room[i].ant_no != 0)
	{
		print_ant_turn((i < 0) ? ant : paths->room[i].ant_no, map->end->name);
		(*ants_at_end)++;
		i--;
	}
	while (i > -1)
	{
		paths->room[i + 1].ant_no = paths->room[i].ant_no;
		if (paths->room[i].ant_no != 0)
			print_ant_turn(paths->room[i].ant_no, \
			map->rooms[paths->room[i + 1].i_next - 1].name);
		i--;
	}
	if (ant != 0 && paths->amount_steps != 1)
	{
		paths->room[0].ant_no = ant;
		print_ant_turn(ant, map->rooms[paths->room[0].i_next - 1].name);
	}
	else if (paths->amount_steps != 1)
		paths->room[0].ant_no = ant;
}

void	run_ant(t_map *map, int *ants_at_end, int ant, t_paths *paths)
{
	if (paths->room[0].ant_no == 0 && paths->amount_steps != 1)
	{
		print_ant_turn(ant, map->rooms[paths->room[0].i_next - 1].name);
		paths->room[0].ant_no = ant;
	}
	else
		push_through_ants(map, ants_at_end, ant, paths);
}

void	starter_ants(t_map *map, t_ants *ants, int i, int *ant_no)
{
	run_ant(map, &((*ants).ants_at_end), (*ant_no)++, &(map->paths[i]));
	(*ants).ants_at_start--;
}

void	launch_ants(t_map *map, char **ways)
{
	t_ants	ants;
	int		ant_no;
	int		i;
	t_ps	*paths_steps;

	ant_no = 1;
	paths_steps = count_path_steps(map, ways, map->amount_ways);
	rank_paths(paths_steps, map->amount_ways);
	map->paths = make_paths(paths_steps, map->amount_ways, ways, map);
	ants.ants_at_start = map->ants;
	ants.ants_at_end = 0;
	while (ants.ants_at_end != map->ants)
	{
		i = -1;
		while (++i < map->amount_ways)
		{
			if (ants.ants_at_start > (issue_sum_prev_steps(paths_steps, i)))
				starter_ants(map, &ants, i, &ant_no);
			else
				push_through_ants(map, &(ants.ants_at_end),
						0, &(map->paths[i]));
		}
		write(1, "\n", 1);
	}
	free(paths_steps);
}
