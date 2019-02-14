/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:01:49 by cheller           #+#    #+#             */
/*   Updated: 2019/02/14 21:40:17 by cheller          ###   ########.fr       */
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
	if(!(buff = ft_strnew(BUFF_SIZE)))
		return(NULL);
	while ((bytes = read(fd, buff, BUFF_SIZE)))
	{
		if(!file_str)
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

int		find_top_vertex(char **tetrimino_matrix)
{
	int		top_vertex;
	int		i;
	int		j;

	i = -1;
	top_vertex = 4;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (tetrimino_matrix[i][j] == '#')
				if (i < top_vertex)
					top_vertex = i;
		}
	}
	return (top_vertex);
}

int		find_outside_vertex(char **tetrimino_matrix)
{
	int		outside_vertex;
	int		i;
	int		j;

	i = -1;
	outside_vertex = 4;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (tetrimino_matrix[i][j] == '#')
				if (j < outside_vertex)
					outside_vertex = j;
		}
	}
	return (outside_vertex);
}

int		find_right_vertex(tet_coords *coord)
{
	int		right_vertex;
	int		i;

	i = -1;
	right_vertex = 0;
	while (++i < 4)
	{
		if (coord->pos[i][0] > right_vertex)
			right_vertex = coord->pos[i][0];
	}
	return (right_vertex);
}

int		find_left_vertex(tet_coords *coord)
{
	int		left_vertex;
	int		i;

	i = -1;
	left_vertex = 4; //!!!!!Исправить
	while (++i < 4)
	{
		if (coord->pos[i][0] < left_vertex)
			left_vertex = coord->pos[i][0];
	}
	return (left_vertex);
}

int		find_bottom_vertex(tet_coords *coord)
{
	int		bottom_vertex;
	int		i;

	i = -1;
	bottom_vertex = 0;
	while (++i < 4)
	{
		if (coord->pos[i][1] > bottom_vertex)
			bottom_vertex = coord->pos[i][1];
	}
	return (bottom_vertex);
}

char	**change_matrix(char **tetrimino_matrix, char letter)
{
	int		top_vertex;
	int		outside_vertex;
	int		i;
	int		j;

	top_vertex = find_top_vertex(tetrimino_matrix);
	printf("top_vertex: %d\n", top_vertex);
	outside_vertex = find_outside_vertex(tetrimino_matrix);
	printf("left_vertex: %d\n", outside_vertex);
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
	//printf("АЛЁ\n");
	print_matrix(tetrimino_matrix);
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

tet_coords	*tet_init_pos(tet_lst *tetrimino, int amount)
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
		while (++y < amount)
		{
			x = -1;
			while (++x < amount)
			{
				if (90 > (tetrimino->tetrimino_matrix)[y][x] && 60 < (tetrimino->tetrimino_matrix)[y][x])
				{
					cur_lst->pos[k][0] = x;
					cur_lst->pos[k][1] = y;
					k++;
				}
			}
		}
		if (tet + 1 != amount)
		{
			tetrimino = tetrimino->next;
			cur_lst->next = (tet_coords*)malloc(sizeof(tet_coords));
			(cur_lst->next)->prev = cur_lst;
			cur_lst = cur_lst->next;
		}
	}
	return (begin);
}

int		calculate_size(int amount)
{
	int		size;

	size = 2;
	while (size * size < amount * 4)
		size++;
	return (size);
}

char	**create_tetris(int amount)
{
	char	**tetris;
	int		size;
	int	i;

	i = -1;
	size = calculate_size(amount);
	printf("size: %d\n", size);
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

void	move_tet(tet_coords *coord, int size)
{
	int	wall;
	int		i;

	i = -1;
	wall = find_right_vertex(coord);
	printf("right: %d\n", wall);
	if (wall + 1 != size)
	{
		while (++i < 4)
			coord->pos[i][0] += 1;
	}
	else if(wall + 1 == size)
	{
		wall = find_left_vertex(coord);
		printf("left: %d\n", wall);
		while (wall > 0)
		{
			i = -1;
			while (++i < 4)
				coord->pos[i][0]--;
			wall--;
		}
		//print_pos(coord, size);
		wall = find_left_vertex(coord);
		printf("left 2: %d\n", wall);
		i = -1;
		wall = find_bottom_vertex(coord);
		if (wall + 1 != size)
			while (++i < 4)
				coord->pos[i][1] += 1;
	}
}

void	arrange_tet(tet_coords *coord, char **tetris, int size)
{
	int	i;
	static int k;

	if (!k)
		k = 0;
//	while (coord)
	while(++k <= 4)
	{
		printf("k = %d\n", k);
		i = -1;
		while (++i < 4)
		{
			if (tetris[coord->pos[i][1]][coord->pos[i][0]] == '.')
				tetris[coord->pos[i][1]][coord->pos[i][0]] = (char)coord->symbol;
			else
			{
				zero_tetris(tetris, coord);
				move_tet(coord, size);
				k--;
				arrange_tet(coord, tetris, size);
				printf("Выполнилось размещение\n");
				return ;
			}
		}
		coord = coord->next;
	}
}

int		process_tetriminos(int fd)
{
	char	*file_str;
	char	**tetris;
	tet_lst	*tetrimino;
	tet_coords	*positions;
	int			amount;

	if(!(file_str = read_tetriminos(fd)))
		return (-1);
	printf ("Выводим весь файл: \n");
	ft_putstr(file_str);
	amount = validate(file_str);
	printf("amount: %d\n", amount);
	if(!(tetrimino = make_lst_tetriminos(file_str, amount)))
		return (-1);
	print_lists(tetrimino);
	positions = tet_init_pos(tetrimino, amount);
	print_pos(positions, amount);
	tetris = create_tetris(amount);
	print_tetris(tetris, amount);
	arrange_tet(positions, tetris, amount);
	printf("Arranged tetris:\n");
	print_tetris(tetris, amount);
	print_pos(positions, amount);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		fd;
	//char	*usage;

	//usage = "usage: ./fillit tetriminos_file\n";
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit tetriminos_file\n");
		exit(0);
	}
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Cannot open file\n");
		return (0);
	}
	process_tetriminos(fd);
	close(fd);
	return (0);
}
