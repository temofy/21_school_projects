/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 17:57:30 by cheller           #+#    #+#             */
/*   Updated: 2019/01/31 17:44:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct		s_tet_lst
{
	struct s_tet_lst	*prev;
	char	**tetrimino_matrix;
	struct s_tet_lst	*next;
}					tet_lst;

#endif
