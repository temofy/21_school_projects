/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:01:49 by cheller           #+#    #+#             */
/*   Updated: 2019/02/21 19:35:17 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

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
			tmp = file_str;
			file_str = ft_strjoin(tmp, buff);
			free(tmp);
		}
		ft_bzero(buff, BUFF_SIZE);
	}
	free(buff);
	return (file_str);
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
	int		i;

	i = -1;
	if (!(tetris = (char**)malloc(sizeof(char*) * size)))
		return (NULL);
	while (++i < size)
	{
		tetris[i] = ft_strnew(size);
		tetris[i] = ft_memset(tetris[i], '.', size);
	}
	return (tetris);
}

int		process_tetriminos(int amount, char *file_str)
{
	char			**tetris;
	t_tet_coords	*positions;
	int				size;

	size = calculate_size(amount);
	positions = tet_init_pos(file_str, amount);
	if (amount < 4)
		size = check_tet_length(positions);
	tetris = create_tetris(size);
	while (arrange(positions, tetris, size) == -1)
	{
		free_tetris(tetris, size);
		zero_positions(positions);
		size++;
		tetris = create_tetris(size);
	}
	free(file_str);
	free_tetriminos(positions);
	print_tetris(tetris, size);
	free_tetris(tetris, size);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		fd;
	char	*file_str;
	int		amount;

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
	file_str = read_tetriminos(fd);
	if ((amount = validate(file_str)) == -1 || amount > 26)
	{
		ft_putstr("error\n");
		return (-1);
	}
	process_tetriminos(amount, file_str);
	close(fd);
	return (1);
}
