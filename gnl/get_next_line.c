/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:53:46 by cheller           #+#    #+#             */
/*   Updated: 2019/02/12 20:25:32 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
//#define ft_strdup strdup

int		free_lst(int fd, t_list_fd *first_lst)
{
	t_list_fd	*prev_lst;
	t_list_fd	*next_lst;

	prev_lst = first_lst;
	next_lst = first_lst;
	while (next_lst)
	{
		if (fd == next_lst->fd)
		{
			if (next_lst->next_lst && prev_lst == next_lst)
				first_lst = next_lst->next_lst;
			if (prev_lst != next_lst)
			{
				if (next_lst->next_lst)
					prev_lst->next_lst = next_lst->next_lst;
				else
					prev_lst->next_lst = NULL;
			}
			free(next_lst);
			return (0);
		}
		prev_lst = next_lst;
		next_lst = next_lst->next_lst;
	}
	return (0);
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

int		check_remainder(t_list_fd *cur_lst, char **line)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	if (cur_lst->tmp_line)
	{
		len = ft_strlen(cur_lst->tmp_line);
		while (cur_lst->tmp_line[i] != '\n' && i < len)
			i++;
		if (i < len)
		{
			tmp = cur_lst->tmp_line;
			*line = ft_strsub(tmp, 0, i);
			cur_lst->tmp_line = ft_strsub(tmp, i + 1, len - i);
			free(tmp);
			return (1);
		}
		else if (i == len)
		{
			if (i != 0)
				*line = ft_strdup(cur_lst->tmp_line);
			free(cur_lst->tmp_line);
			cur_lst->tmp_line = NULL;
		}
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int			bytes;
	t_list_fd	*cur_lst;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	*line = NULL;
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(fd, NULL);
	cur_lst = find_lst(fd, fd_lists);
	//printf("start\n");
	if (check_remainder(cur_lst, line))
		return (1);
	while (!(cur_lst->tmp_line))
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[bytes] = '\0';
		if (bytes == 0 && !(*line) &&!(cur_lst->tmp_line))
			return (free_lst(fd, fd_lists));
		else if (bytes == 0)
			return (1);
		tmp = ft_strtchr(buff, '\n');
		if (!tmp)
		{
			if (*line)
			{
				//printf("A potom\n");
				tmp = *line;
				*line = ft_strjoin(*line, buff);
				free(tmp);
			}
			else
			{
				//printf("kek1\n");
				*line = ft_strdup(buff);
				//printf("kek2\n");
			}
		}
		else
		{
			if (*line)
				*line = ft_strjoin(*line, tmp);
			else
				*line = ft_strdup(tmp);
			cur_lst->tmp_line = ft_strdup(ft_strpchr(buff, '\n'));
			free(tmp);
			break ;
		}
	}
	return (1);
}
