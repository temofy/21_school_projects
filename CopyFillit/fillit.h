/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:57:30 by cheller           #+#    #+#             */
/*   Updated: 2019/02/20 20:09:21 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>
# define POINT tetris[coord->pos[i][1]][coord->pos[i][0]]

typedef struct		s_tet_coords
{
	struct	s_tet_coords	*prev;
	int		symbol;
	int		pos[4][2];
	struct s_tet_coords	*next;
}					tet_coords;

int						validate(char *line);
void					print_matrix(char **matrix);
void					print_lists(tet_lst *begin);
void					print_tetris(char **tetris, int size);
void					print_pos(tet_coords *coords);
int						find_top_outside_vertex(char **tetrimino_matrix);
int						find_outside_vertex(char **tetrimino_matrix);
int						find_right_vertex(tet_coords *coord);
int						find_left_vertex(tet_coords *coord);
int						find_top_vertex(tet_coords *coord);
int						find_bottom_vertex(tet_coords *coord);

#endif