/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:53:46 by cheller           #+#    #+#             */
/*   Updated: 2019/02/07 12:48:01 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#define ft_strdup strdup

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
	while (fd_list)
	{
		if (fd_list->fd == fd)
			return(fd_list);
		fd_list = fd_list->next_lst;
	}
	return (NULL);
}

int	read_line(int fd, t_list_fd *fd_list, char *buff)
{
	int	bytes;
	char	*tmp;

	ft_bzero(buff, BUFF_SIZE);
	if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
		return (-1);
	if (bytes == 0)
		return (0);
	if((find_lst(fd, fd_list)))
	{
		fd_list = find_lst(fd, fd_list);
		tmp = fd_list->tmp_line;
		fd_list->tmp_line = ft_strjoin(fd_list->tmp_line, buff);
		free(tmp);
		if (!(ft_isthere_chr(fd_list->tmp_line, '\n')))
			read_line(fd, fd_list, buff);
		return (1);
	}
	fd_list = ft_find_last_lst(fd_list);
	fd_list->next_lst = ft_lstnew_fd(fd, ft_strdup(buff));
	fd_list = fd_list->next_lst;
	if (!(ft_isthere_chr(fd_list->tmp_line, '\n')))
		read_line(fd, fd_list, buff);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char			buff[BUFF_SIZE + 1];
	int 			rtn;
	char			*tmp;
	t_list_fd		*cur_lst;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(fd, ft_strdup(buff));
	if ((rtn = read_line(fd, fd_lists, buff)) == -1)
			return (-1);
	//ft_bzero(buff, BUFF_SIZE);
	cur_lst = find_lst(fd, fd_lists);
	if ((!(cur_lst) || (!(ft_strlen(cur_lst->tmp_line)) && !rtn)))
		return (0);
	if ((tmp = ft_strtchr(cur_lst->tmp_line, '\n')) == NULL)
	{
		*line = ft_strdup(cur_lst->tmp_line);
		free_line(fd, fd_lists);
		return (1);
	}
	*line = tmp;
	tmp  = cur_lst->tmp_line;
	cur_lst->tmp_line = ft_strdup((ft_strchr(cur_lst->tmp_line, '\n')) + 1);
	free(tmp);
	return (1);
}
