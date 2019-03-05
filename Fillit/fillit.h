/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:57:30 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 19:28:24 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>
# define POINT tetris[coord->pos[i][1]][coord->pos[i][0]]
# define BUFF_SIZE 10

typedef struct			s_tet_coords
{
	struct s_tet_coords	*prev;
	int					symbol;
	int					pos[4][2];
	struct s_tet_coords	*next;
}						t_tet_coords;

int						validate(char *line);
void					print_tetris(char **tetris, int size);
int						find_right_vertex(t_tet_coords *coord);
int						find_left_vertex(t_tet_coords *coord);
int						find_top_vertex(t_tet_coords *coord);
int						find_bottom_vertex(t_tet_coords *coord);

void					zero_tetris(char **tetris, t_tet_coords *coord);
void					zero_positions(t_tet_coords *positions);
void					free_tetris(char **tetris, int size);
void					free_tetriminos(t_tet_coords *tetriminos);

int						check_tet_length(t_tet_coords *tetrimino);
int						arrange(t_tet_coords *coord, char **tetris, int size);
void					return_start_pos(t_tet_coords *coord);
int						move_tet(t_tet_coords *coord, int size);
t_tet_coords			*tet_init_pos(char *str_tetriminos, int amount);
#endif
