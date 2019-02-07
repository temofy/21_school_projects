/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:53:46 by cheller           #+#    #+#             */
/*   Updated: 2019/02/07 18:09:04 by cheller          ###   ########.fr       */
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

/*int	read_line(int fd, t_list_fd *fd_list, char *buff)
{
	int	bytes;
	char	*tmp;

	ft_bzero(buff, BUFF_SIZE);
	if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
		return (-1);
	if (bytes == 0)
		return (0);
	if (!(ft_isthere_chr(buff, '\n')))
		return read(fd, fd_list, buff);


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
}*/

int	get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int		bytes;
	int			is_line;

	is_line = 0;
	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	tmp = NULL;
	*line = NULL;
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(fd, NULL);
	//printf("tmp_line: %s\n", fd_lists->tmp_line);
	if (fd_lists->tmp_line)
	{
		if (ft_isthere_chr(fd_lists->tmp_line, '\n'))
		{
			*line = ft_strtchr(fd_lists->tmp_line, '\n');
			tmp = fd_lists->tmp_line;
			fd_lists->tmp_line = ft_strjoin(ft_strpchr(tmp, '\n'), "");
			free(tmp);
			is_line = 1;
		}
		else
		{
			tmp = *line;
			*line = ft_strdup(fd_lists->tmp_line);
			fd_lists->tmp_line = NULL;
			if (tmp)
				free(tmp);
		}
	}
	while (!is_line && !(fd_lists->tmp_line))
	{
		ft_bzero(buff, BUFF_SIZE + 1);
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (bytes == 0 && !(*line) &&!(fd_lists->tmp_line))
			return (0);
		else if (bytes == 0)
			return (1);
		//printf("buff: %s\n", buff);
		if (ft_isthere_chr(buff, '\n'))
		{
			is_line = 1;
			tmp = ft_strtchr(buff, '\n');
			if (*line)
				*line = ft_strjoin(*line, tmp);
			else
				*line = ft_strdup(tmp);
			free(tmp);
			fd_lists->tmp_line = ft_strjoin(ft_strpchr(buff, '\n'), "");
		}
		else
		{
			tmp = *line;
			if (*line)
				*line = ft_strjoin(*line, buff);
			else
				*line = ft_strdup(buff);
			if (tmp)
				free(tmp);
			//printf("line: %s\n", *line);
		}
	}
	return (1);

	/*cur_lst = find_lst(fd, fd_lists);
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
	return (1);*/
}
