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
	int 	shortest_steps;
	int 	*shortest_way;
	char 	**file;
}				t_map;

typedef struct		s_node
{
	int				i_room;
	//int 			level;
	int				entrances;
	int 			exits;
	struct s_node	*next_room;
	struct s_node	*prev_room;
}					t_node;

typedef struct		s_node2
{
	int				i_room;
	//int 			level;
	int				entrances;
	int 			exits;
	struct s_node2	**next_room;
	struct s_node2	**prev_room;
	int 			prev_for_bfs;
	int 			next_for_bfs;
}					t_node2;

typedef struct		s_path_steps
{
	int 			way_steps;
	int 			way_begin;
}					t_ps;

typedef struct		s_queue
{
	t_node2			*room;
	struct s_queue	*next_in_q;
}					t_queue;

/*typedef struct 		s_rooms
{
	int				i_next;
	int 			ant_no;
}					t_rooms;*/

/*typedef struct		s_paths
{
	int 			amount_steps;
	int				*each_room;
	//int				**room;
}					t_paths;*/

/*typedef struct		s_ants
{
	int 			ant_no;
	int 			path_no;
	int 			room_no
}					t_ants;*/

typedef struct 		s_rooms
{
	int				i_next;
	int 			ant_no;
}					t_rooms;

typedef struct		s_paths
{
	int 			amount_steps;
	t_rooms			*room;
}			t_paths;

typedef struct		s_num_q
{
	int 			nbr;
	int 			prev_nbr;
	int 			layer_lvl;
	struct s_num_q	*next_in_q;
}					t_num_q;

/*typedef struct		s_queue
{
	t_node			*room;
	struct s_queue	*next_in_q;
}				t_queue;*/

int		reading_map();
int 	free_map(t_map *map, int status);
int 	count_links(char **file, int i);
int 	count_rooms(char **file, int i);
int 	reading_rooms(char *str, t_map *map);
int 	reading_se(char *str, t_room **se);

#endif
