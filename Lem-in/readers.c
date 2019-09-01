/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 12:04:17 by cheller           #+#    #+#             */
/*   Updated: 2019/08/25 12:04:18 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	reading_rooms(char *str, t_map *map)
{
	char		**room;
	static int	i = 0;
	long		value;
	int			rtn;

	rtn = (!str) ? -1 : 1;
	room = ft_strsplit(str, ' ');
	rtn = (rtn == 1 && room && room[0][0] == 'L') ? -1 : 1;
	if (rtn == 1 && map->rooms)
	{
		map->rooms[i].name = ft_strdup(room[0]);
		value = ft_atoi_f(room[1], &rtn);
		if (rtn == 1)
			map->rooms[i].x = (int)value;
		value = ft_atoi_f(room[2], &rtn);
		if (rtn == 1)
			map->rooms[i].y = (int)value;
		i++;
	}
	ft_arrdel(&room);
	return (rtn);
}

int	reading_se(char *str, t_room **se)
{
	char	**room;
	long	value;
	int		rtn;

	rtn = (!str || ft_count_words(str) != 3) ? -1 : 1;
	room = (rtn == 1) ? ft_strsplit(str, ' ') : NULL;
	*se = (rtn == 1) ? (t_room *)ft_memalloc(sizeof(t_room)) : NULL;
	rtn = (*se == NULL) ? -1 : 1;
	rtn = ((rtn == 1 && room[0][0] == 'L') || rtn == -1) ? -1 : 1;
	if (rtn == 1)
	{
		(*se)->name = ft_strdup(room[0]);
		value = ft_atoi_f(room[1], &rtn);
		if (rtn == 1)
			(*se)->x = (int)value;
		value = ft_atoi_f(room[2], &rtn);
		if (rtn == 1)
			(*se)->y = (int)value;
	}
	ft_arrdel(&room);
	return (rtn);
}

int	reading_ants(char *string, int *ants)
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
