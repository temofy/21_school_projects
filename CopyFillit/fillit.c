/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:01:49 by cheller           #+#    #+#             */
/*   Updated: 2019/02/20 20:08:58 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#define BUFF_SIZE 10

char	*read_tetriminos(int fd)
{
	char	*buff;
	int		bytes;
	char	*file_str;
	char	*tmp;

	file_str = NULL;
	if (!(buff = ft_strnew(BUFF_SIZE)))
		return (NULL);
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
		cur_lst->symbol = chr++;
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
					cur_lst->pos[k++][1] = y;
				}
				str_tetriminos++;
			}
			str_tetriminos++;
		}
		str_tetriminos++;
		return_start_pos(cur_lst);
		if (amount)
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
	tetris = (char**)malloc(sizeof(char*) * size);
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
	else if (wall + 1 == size)
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
				return (-1);
			}
			i = -1;
		}
	}
	if (arrange_tet(coord->next, tetris, size) == -1)
	{
		zero_tetris(tetris, coord);
		if (move_tet(coord, size) == -1)
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

void	free_tetris(char **tetris, int size)
{
	while (size)
		free(tetris[size - 1]);
	free(tetris);
}

int		process_tetriminos(int fd)
{
	char	*file_str;
	char	**tetris;
	tet_coords	*positions;
	int			amount;
	int			size;

	file_str = read_tetriminos(fd);
	if ((amount = validate(file_str)) == -1)
	{
		ft_putstr("error\n");
		return (-1);
	}
	size = calculate_size(amount);
	positions = tet_init_pos(file_str, amount);
	if (amount < 4)
		size = check_tet_length(positions);
	tetris = create_tetris(size);
	while (arrange_tet(positions, tetris, size) == -1)
	{
		free_tetris(tetris, size);
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
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr("Cannot open file\n");
		return (-1);
	}
	process_tetriminos(fd);
	close(fd);
	return (1);
}
