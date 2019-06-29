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

	while (*string)
	{
		if (*string < '0' || *string > '9')
			return (-1);
		*ants = *ants * 10 + (*string - '0');
		string++;
	}
	return (1);
}

int 	free_map(t_map *map)
{
	return (1);
}

int 	reading_rooms()
{
	return (1);
}

int 	reading_links()
{
	return (1);
}

int		reading_map()
{
	char  	*string;
	int 	start_room;
	int 	end_room;
	t_map	map;

	while (get_next_line(0, &string))
	{
		if (map.ants == -1)
			if (reading_ants(string) == -1)
				return (free_map(&map));
		if (ft_strcmp("##start", string) == 0)
			start_room = 1;
		if (start_room)
			if (reading_rooms() == -1)
				return (free_map(&map));
		if (ft_strcmp("##end", string) == 0)
			end_room = 1;
		if (end_room)
			if (reading_rooms() == -1)
				return (free_map(&map));
		if (ft_isthere_chr(operation, '-') == 1)
			//bla bla
	}
	return (1);
}
