/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:43:24 by cheller           #+#    #+#             */
/*   Updated: 2019/06/29 19:43:27 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN__H
#define LEM_IN__H

# include "libft/libft.h"
# include <stdio.h>

typedef struct	s_room
{
	char	*name;
	int 	x;
	int 	y;
}				t_room;

typedef struct	s_links
{
	char	*room1;
	char 	*room2;
}				t_links;

typedef struct	s_map
{
	int 	ants;
	t_room 	*rooms;
	int 	nbrs_rooms;
	t_room	*start;
	t_room	*end;
	t_links	*links;
	int 	nbrs_links;
	char 	*file;
}				t_map;

int		reading_map();
int 	free_map(t_map *map, int status);
int 	count_links(char **file, int i);
int 	count_rooms(char **file, int i);
int 	reading_rooms(char *str, t_map *map);
int 	reading_se(char *str, t_room **se);

#endif