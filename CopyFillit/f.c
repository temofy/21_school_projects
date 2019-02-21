/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:01:49 by cheller           #+#    #+#             */
/*   Updated: 2019/02/20 18:24:16 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>
#define BUFF_SIZE 10

char	*read_tetriminos(int fd)
{
	char	*buff;
	int		bytes;
	char	*file_str;
	char	*tmp;

	file_str = NULL;
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return(NULL);
	while ((bytes = read(fd, buff, BUFF_SIZE)))
	{
		if (!file_str)
			file_str = ft_strdup(buff);
		else
		{
			tmp = ft_strnew(ft_strlen(file_str));
			tmp = ft_strcpy(tmp, file_str);
			file_str = ft_strjoin(tmp, buff);
			free(tmp);
		}
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	return (file_str);
}

char	**change_matrix(char **tetrimino_matrix, char letter)
{
	int		top_vertex;
	int		outside_vertex;
	int		i;
	int		j;

	top_vertex = find_top_outside_vertex(tetrimino_matrix);
	outside_vertex = find_outside_vertex(tetrimino_matrix);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (tetrimino_matrix[i][j] == '#')
			{
				tetrimino_matrix[i - top_vertex][j - outside_vertex] = letter;
				if (i != (i - top_vertex) || (j != (j - outside_vertex)))
					tetrimino_matrix[i][j] = '.';
			}
		}
	}
	return (tetrimino_matrix);
}

char	**write_into_matrix(char **tetrimino_matrix, char *str_tetriminos)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*str_tetriminos && i < 4)
	{
		if (*str_tetriminos != '\n')
		{
			tetrimino_matrix[i][j] = *str_tetriminos;
			j++;
			if (j  == 4)
			{
				i++;
				j = 0;
			}
		}
		str_tetriminos++;
	}
	return (tetrimino_matrix);
}

char	**save_tetrimino(char *str_tetriminos)
{
	char		**tetrimino_matrix;
	int		i;
	static char	letter;

	if (!letter)
		letter = 'A';
	i = -1;
	tetrimino_matrix = (char**)malloc(sizeof(char*) * 5);
	while (++i < 4)
	{
		if(!(tetrimino_matrix[i] = ft_strnew(4)))
			return(NULL);//free
	}
	tetrimino_matrix = write_into_matrix(tetrimino_matrix, str_tetriminos);
	tetrimino_matrix = change_matrix(tetrimino_matrix, letter);
	letter++;
	return (tetrimino_matrix);
}

tet_lst	*create_lstnew(tet_lst *prev, tet_lst *next)
{
	tet_lst	*cur_lst;

	if (!(cur_lst = (tet_lst*)malloc(sizeof(tet_lst))))
		return (NULL); //free
	cur_lst->prev = prev;
	cur_lst->tetrimino_matrix = NULL;
	cur_lst->next = next;
	return (cur_lst);
}

tet_lst	*make_lst_tetriminos(char *str_tetriminos, int amount_tetriminos)
{
	tet_lst	*begin_lst;
	tet_lst	*cur_lst;
	int		i;

	i = 0;
	begin_lst = create_lstnew(NULL, NULL);
	begin_lst->tetrimino_matrix = save_tetrimino(str_tetriminos);
	str_tetriminos += 21;
	while (++i < amount_tetriminos)
	{
		if (!begin_lst->next)
		{
			cur_lst = create_lstnew(begin_lst, NULL);
			cur_lst->tetrimino_matrix = save_tetrimino(str_tetriminos);
			begin_lst->next = cur_lst;
		}
		else
		{
			cur_lst->next = create_lstnew(cur_lst, NULL);
			cur_lst = cur_lst->next;
			cur_lst->tetrimino_matrix = save_tetrimino(str_tetriminos);
		}
		str_tetriminos += 21;
	}
	return (begin_lst);
}

void	return_start_pos(tet_coords *coord)
{
	int		left_vertex;
	int		top_vertex;
	int		i;

	left_vertex = find_left_vertex(coord);
	top_vertex = find_top_vertex(coord);
	while (left_vertex)
	{
		i = -1;
		while (++i < 4)
			coord->pos[i][0]--;
		left_vertex--;
	}
	while (top_vertex)
	{
		i = -1;
		while (++i < 4)
			coord->pos[i][1]--;
		top_vertex--;
	}
}

tet_coords	*tet_init_pos(char *str_tetriminos, int amount)
{
	int			tet;
	char		chr;
	int			y;
	int			x;
	int			k;
	tet_coords	*begin;
	tet_coords	*cur_lst;

	tet = -1;
	chr = 'A';
	begin = (tet_coords*)malloc(sizeof(tet_coords));
	begin->prev = NULL;
	cur_lst = begin;
	while (++tet < amount)
	{
		cur_lst->symbol = chr;
		chr++;
		y = -1;
		k = 0;
		while (++y < 4)
		{
			x = -1;
			while (++x < 4)
			{
				if (*str_tetriminos == '#')
				{
					cur_lst->pos[k][0] = x;
					cur_lst->pos[k][1] = y;
					k++;
				}
				str_tetriminos++;
			}
			str_tetriminos++;
		}
		str_tetriminos++;
		return_start_pos(cur_lst);
		if (tet + 1 != amount)
		{
			cur_lst->next = (tet_coords*)malloc(sizeof(tet_coords));
			(cur_lst->next)->prev = cur_lst;
			cur_lst = cur_lst->next;
		}
		else
			cur_lst->next = NULL;
	}
	return (begin);
}

/*tet_coords	*tet_init_pos(tet_lst *tetrimino, int amount)
{
	char		chr;
	int			y;
	int			x;
	int			k;
	tet_coords	*begin;
	tet_coords	*cur_lst;

	chr = 'A';
	begin = (tet_coords*)malloc(sizeof(tet_coords));
	begin->prev = NULL;
	cur_lst = begin;
	while (amount--)
	{
		cur_lst->symbol = chr;
		chr++;
		y = -1;
		k = 0;
		while (++y < 4)
		{
			x = -1;
			while (++x < 4)
			{
				if (90 > (tetrimino->tetrimino_matrix)[y][x] && 60 < (tetrimino->tetrimino_matrix)[y][x])
				{
					cur_lst->pos[k][0] = x;
					cur_lst->pos[k++][1] = y;
				}
			}
		}
		if (amount)
		{
			tetrimino = tetrimino->next;
			cur_lst->next = (tet_coords*)malloc(sizeof(tet_coords));
			(cur_lst->next)->prev = cur_lst;
			cur_lst = cur_lst->next;
		}
		else
			cur_lst->next = NULL;
	}
	return (begin);
}*/

int		calculate_size(int amount)
{
	int		size;

	if (amount == -1)
		return (-1);
	size = 2;
	while (size * size < amount * 4)
		size++;
	return (size);
}

char	**create_tetris(int size)
{
	char	**tetris;
	int	i;

	i = -1;
	tetris = (char**)malloc(sizeof(char*) * size + 1);
	while (++i < size)
	{
		tetris[i] = ft_strnew(size);
		tetris[i] = ft_memset(tetris[i], '.', size);
	}
	return (tetris);
}

void	zero_tetris(char **tetris, tet_coords *coord)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		if (POINT == coord->symbol)
			POINT = '.';
	}
}

int		move_tet(tet_coords *coord, int size)
{
	int	wall;
	int		i;

	i = -1;
	wall = find_right_vertex(coord);
	if (wall + 1 != size)
		while (++i < 4)
			coord->pos[i][0] += 1;
	else if(wall + 1 == size)
	{
		wall = find_bottom_vertex(coord);
		if (wall + 1 == size)
			return (-1);
		i = -1;
		while (++i < 4)
			coord->pos[i][1] += 1;
		wall = find_left_vertex(coord);
		while (wall-- > 0)
		{
			i = -1;
			while (++i < 4)
				coord->pos[i][0]--;
		}
	}
	return (1);
}

int	arrange_tet(tet_coords *coord, char **tetris, int size)
{
	int	i;

	if (coord == NULL)
		return (1);
	i = -1;
	while (++i < 4)
	{
		if (tetris[coord->pos[i][1]][coord->pos[i][0]] == '.')
			tetris[coord->pos[i][1]][coord->pos[i][0]] = (char)coord->symbol;
		else
		{
			zero_tetris(tetris, coord);
			if (move_tet(coord, size) == -1)
			{
				return_start_pos(coord);
				//printf("Fail! Фигура: %c не поставилась\n", coord->symbol);
				return (-1);
			}
			i = -1;
		}
	}
	//printf("Фигура: %c успешно поставлена\n", coord->symbol);
	//print_tetris(tetris, size);
	if (arrange_tet(coord->next, tetris, size) == -1)
	{
		zero_tetris(tetris, coord);
		if(move_tet(coord, size) == -1)
		{
			return_start_pos(coord);
			return (-1);
		}
		if (arrange_tet(coord, tetris, size) == -1)
			return (-1);
	}
	return (1);
}

int		check_tet_length(tet_coords *tetrimino)
{
	int		length;
	int		i;
	tet_coords	*cur_lst;

	cur_lst = tetrimino;
	length = 0;
	while (cur_lst)
	{
		i = -1;
		while (++i < 4)
		{
			if (length < cur_lst->pos[i][0])
				length = cur_lst->pos[i][0];
			if (length < cur_lst->pos[i][1])
				length = cur_lst->pos[i][1];
		}
		cur_lst = cur_lst->next;
	}
	return (length + 1);
}

void	zero_positions(tet_coords *positions)
{
	tet_coords	*cur;

	cur = positions;
	while (cur)
	{
		return_start_pos(cur);
		cur = cur->next;
	}
}

int		process_tetriminos(int fd)
{
	char	*file_str;
	char	**tetris;
	tet_lst	*tetrimino;
	tet_coords	*positions;
	int			amount;
	int			size;

	if(!(file_str = read_tetriminos(fd)))
		return (-1);
	if ((amount = validate(file_str)) == -1)
	{
		ft_putstr("error\n");
		return (-1);
	}
	if(!(tetrimino = make_lst_tetriminos(file_str, validate(file_str))))
		return (-1);
	size = calculate_size(amount);
	positions = tet_init_pos(file_str, amount);
	if (amount < 4)
		size = check_tet_length(positions);
	tetris = create_tetris(size);
	while (arrange_tet(positions, tetris, size) == -1)
	{
		//free
		zero_positions(positions);
		size++;
		tetris = create_tetris(size);
	}
	print_tetris(tetris, size);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		fd;

	if (argc != 2)
	{
		ft_putstr("usage: ./fillit tetriminos_file\n");
		exit(-1);
	}
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Cannot open file\n");
		return (-1);
	}
	process_tetriminos(fd);
	close(fd);
	return (1);
}
