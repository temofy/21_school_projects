/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:01:49 by cheller           #+#    #+#             */
/*   Updated: 2019/02/03 16:48:56 by cheller          ###   ########.fr       */
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

void	print_matrix(char **matrix)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		ft_putstr(matrix[i]);
		ft_putchar('\n');
	}
}

void	print_lists(tet_lst *begin)
{
	tet_lst	*cur_lst;

	cur_lst = begin;
	while (cur_lst)
	{
		print_matrix(cur_lst->tetrimino_matrix);
		ft_putchar('\n');
		cur_lst = cur_lst->next;
	}
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

char	**change_matrix(char **tetrimino_matrix, char letter)
{
	int		top_vertex;
	int		outside_vertex;
	int		i;
	int		j;

	top_vertex = find_top_vertex(tetrimino_matrix);
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

int		calculate_size(int amount)
{
	int		size;

	size = 2;
	while (size * size <= amount * 4)
		size++;
	return (size);
}

char	**arrange_tetriminos(tet_lst *tetrimino, int amount)
{
	tet_lst	cur_tet;
	static char	**tetris;
	int		size;

	size = calculate_size(amount);
	cur_tet = tetrimino;

}

int		process_tetriminos(int fd)
{
	char	*file_str;
	char	**tetris;
	tet_lst	*tetrimino;

	if(!(file_str = read_tetriminos(fd)))
		return (-1);
	printf ("Выводим весь файл: \n");
	ft_putstr(file_str);
	printf("Обрабатываем: \n");
	//validate
	if(!(tetrimino = make_lst_tetriminos(file_str, 4)))
		return (-1);
	tetris = arrange_tetriminos(tetrimino);
	printf("Выводим все листы: \n");
	print_lists(tetrimino);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		fd;
	char	*usage;

	usage = "usage: ./fillit tetriminos_file\n";
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
