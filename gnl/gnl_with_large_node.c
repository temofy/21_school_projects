/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:07:18 by cheller           #+#    #+#             */
/*   Updated: 2019/02/11 18:43:52 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

void		free_line(int fd, t_list_fd *first_lst)
{
	t_list_fd	*prev_lst;
	t_list_fd	*next_lst;

	prev_lst = first_lst;
	next_lst = first_lst;
	while (next_lst)
{
		if (fd == next_lst->fd)
		{
			if (prev_lst != next_lst)
			{
				if (next_lst->next_lst)
					prev_lst->next_lst = next_lst->next_lst;
				else
					prev_lst->next_lst = NULL;
			}
			free(next_lst->tmp_line);
			free(next_lst);
			return ;
		}
		prev_lst = next_lst;
		next_lst = next_lst->next_lst;
	}
}

t_list_fd *find_lst(int fd, t_list_fd *fd_list)
{
	t_list_fd	*begin;

	begin = fd_list;
	while (fd_list)
	{
		if (fd_list->fd == fd)
			return(fd_list);
		fd_list = fd_list->next_lst;
	}
	begin = ft_find_last_lst(begin);
	begin->next_lst = ft_lstnew_fd(fd, NULL);
	return (begin->next_lst);
}

int		write_lines(int fd, t_list_fd *cur_lst, char **line, int bytes)
{
	char	*tmp;
	int	length;

	length = 0;
	if ((length = ft_strposchr(cur_lst->tmp_line, '\n')) == -1)
	{
		if (bytes == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(cur_lst->tmp_line);
		free(cur_lst->tmp_line);
		cur_lst->tmp_line = NULL;
	}
	else
	{
		*line = ft_strsub(cur_lst->tmp_line, 0, length);
		tmp = ft_strdup(cur_lst->tmp_line + length + 1);
		free(cur_lst->tmp_line);
		cur_lst->tmp_line = tmp;
		/*if ((cur_lst->tmp_line)[0] == '\0')
		{
			free(cur_lst->tmp_line);
			cur_lst->tmp_line = NULL;
		}*/
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	//int				size;
	int			bytes;
	//t_list_fd	*cur_lst;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(fd, NULL);
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (fd_lists->tmp_line == NULL)
			fd_lists->tmp_line = ft_strnew(1);
		tmp = ft_strjoin(fd_lists->tmp_line, buff);
		free(fd_lists->tmp_line);
		fd_lists->tmp_line = tmp;
	}
	if (bytes == -1)
		return (-1);
	else if (bytes == 0 && !(fd_lists->tmp_line))
		return (0);
	return (write_lines(fd, fd_lists, line, bytes));
}
	/**line = NULL;
	size = -1;
	cur_lst = find_lst(fd, fd_lists);
	if (check_remainder(cur_lst, line))
		return (1);
	while (size == -1)
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (bytes == 0 && !(*line) &&!(cur_lst->tmp_line))
			return (0);
		else if (bytes == 0)
			return (1);
		buff[bytes] = '\0';
		size = ft_strposchr(buff, '\n');
		if (size != -1)
		{
			*line = ft_strsub(buff, 0, size - 1);
			if (!(cur_lst->tmp_line))
				cur_lst->tmp_line = ft_strsub(buff, size + 1, BUFF_SIZE - size);
			else
			{
				tmp = cur_lst->tmp_line;
				cur_lst->tmp_line = ft_strjoin(cur_lst->tmp_line, buff + size);
				free(tmp);
			}
		}
		else
		{
			if ((cur_lst->tmp_line))
			{
				tmp = cur_lst->tmp_line;
				cur_lst->tmp_line = ft_strjoin(cur_lst->tmp_line, buff);
				free(tmp);
			}
			else
				cur_lst->tmp_line = ft_strdup(buff);
		}

		if (!tmp)
		{
			if (*line)
			{
				tmp = *line;
				*line = ft_strjoin(*line, buff);
				free(tmp);
				tmp = NULL;
			}
			else
				*line = ft_strdup(buff);
		}
		else
		{
			if (*line)
				*line = ft_strjoin(*line, tmp);
			else
				*line = tmp;
			cur_lst->tmp_line = ft_strdup(ft_strpchr(buff, '\n'));
		}
	}
	return (1);
}*/
