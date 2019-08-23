/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_entrances.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:56:27 by cheller           #+#    #+#             */
/*   Updated: 2019/08/22 20:56:29 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
