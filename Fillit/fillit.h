/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:57:30 by cheller           #+#    #+#             */
/*   Updated: 2019/02/15 14:42:16 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>
# define POINT tetris[coord->pos[i][1]][coord->pos[i][0]]
typedef struct		s_tet_lst
{
	struct s_tet_lst	*prev;
	char	**tetrimino_matrix;
	struct s_tet_lst	*next;
}					tet_lst;

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
#endif
