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

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>

typedef struct		s_room
{
	char	*name;
	int		x;
	int		y;
}					t_room;

typedef struct		s_links
{
	char	*room1;
	char	*room2;
}					t_links;

typedef struct		s_rooms
{
	int	i_next;
	int	ant_no;
}					t_rooms;

typedef struct		s_paths
{
	int			amount_steps;
	t_rooms		*room;
}					t_paths;

typedef struct		s_map
{
	int		ants;
	t_room	*rooms;
	int		nbrs_rooms;
	t_room	*start;
	t_room	*end;
	t_links	*links;
	int		nbrs_links;
	char	**file;
	t_paths	*paths;
	int		amount_ways;
}					t_map;

typedef struct		s_node2
{
	int				i_room;
	int				entrances;
	int				exits;
	struct s_node2	**next_room;
	struct s_node2	**prev_room;
	int				prev_for_bfs;
	int				next_for_bfs;
}					t_node2;

typedef struct		s_path_steps
{
	int	way_steps;
	int	way_begin;
}					t_ps;

typedef struct		s_queue
{
	t_node2			*room;
	struct s_queue	*next_in_q;
}					t_queue;

typedef struct		s_amount_ants
{
	int	ants_at_start;
	int	ants_at_end;
}					t_ants;

typedef struct		s_num_q
{
	int				nbr;
	int				prev_nbr;
	int				layer_lvl;
	struct s_num_q	*next_in_q;
}					t_num_q;

int					lem_in();
int					free_map(t_map *map, int status);
int					count_links(char **file, int i);
int					count_rooms(char **file, int i);
int					reading_rooms(char *str, t_map *map);
int					reading_se(char *str, t_room **se);
void				free_paths(t_paths **paths, int amount);
void				free_rooms(t_node2 **first_room, int amount_rooms);
void				launch_ants(t_map *map, char **ways);
t_ps				*count_path_steps(t_map *map, char **ways, int amount_ways);
void				rank_paths(t_ps *paths, int amount_ways);
int					issue_sum_prev_steps(t_ps *path, int cur_i);
int					find_last_busy_room(t_paths *paths);
t_paths				*make_paths(t_ps *paths_steps, int amount_ways, \
					char **ways, t_map *map);
int					nbr_len(int n);
int					find_last_busy_room(t_paths *paths);
t_num_q				*find_end_of_n_queue(t_num_q *q);
int					find_next_i(char **ways, int *neighbour, int vertex_i,
					char *checked);
int					find_index_room(t_map *map, char *room);
int					find_next_without_check(char **ways, int *neighbour,
					int vertex_i);
int 				finding_non_intersecting_ways(t_map *map, char **ways,
					t_node2 *first_room);
void				initialize_map(t_map *map);
int					reading_ants(char *string, int *ants);
int					record_rooms(t_map *map, char **file, int *i, int amount);
int					handler_links(t_map *map, char **file, int *i);
int					check_map(t_map *map, char ***ways, t_node2 **first_room);
int					count_neighbors(char **ways, int vertex_i, char *checked,
					t_map *map);
int					count_non_intersecting_ways(char **ways);
t_node2				*create_nodes(t_map *map, char **directions);
int					check_map(t_map *map, char ***ways, t_node2 **first_room);
int					check_coordinates(t_map *map);
int					check_vertex_entry(char **ways, int vertex, t_map *map);
char				**set_the_direction(char **ways, t_map *map);
int 				make_validate_ways(t_map *map, char ***adjacency_matrix);
int					non_repeatability_check(t_map *map);
int					exitsamount_exits(char **directions, int room);
void				assign_next_rooms(t_node2 *rooms, t_node2 *cur_room,
					char **dir);
void				assign_prev_rooms(t_node2 *rooms, t_node2 *cur_room,
					char **dir, int size);
int					handler_hashes(t_map *map, char **file, int *i);
int 				handler_links(t_map *map, char **file, int *i);
int					skip_comments(char **file, int *i);
int 				record_links(t_map *map, char **file, int *i);
char				*links_split(char *str, int room);
void				record_shortest_way(char **ways, t_node2 *end);
int					make_validate_ways(t_map *map, char ***adjacency_matrix);
int					exitsamount_entrances(char **directions, int room, int size);
int					bfs(t_map *map, char **ways, t_node2 *first_node);

void	print_directs(char **directions, t_map *map);
void	print_matrix(char **matrix);
#endif
