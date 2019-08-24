/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:04:58 by cheller           #+#    #+#             */
/*   Updated: 2019/08/24 16:05:00 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_links(char **file, int i)
{
	int		links;

	links = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 1 && ft_isthere_chr(file[i], '-'))
		{
			links++;
			i++;
			continue ;
		}
		else
			break ;
	}
	return (links);
}

int		count_rooms(char **file, int i)
{
	int		rooms;

	rooms = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 3 && !ft_isthere_chr(file[i], '#'))
		{
			if ((ft_strcmp(file[i - 1], "##start") != 0)
			&& (ft_strcmp(file[i - 1], "##end") != 0))
				rooms++;
		}
		i++;
	}
	return (rooms);
}

int		count_neighbors(int vertex_i, char *checked, t_map *map)
{
	int neighbour;
	int amount;

	neighbour = 0;
	amount = 0;
	if (vertex_i == map->nbrs_rooms + 1)
		return (0);
	while (map->ways[neighbour])
	{
		if (map->ways[vertex_i][neighbour] == '1'
			&& (checked[neighbour] != '1'))
			amount++;
		neighbour++;
	}
	return (amount);
}

int		count_non_intersecting_ways(char **ways)
{
	int	i;
	int	amount_ways;

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
