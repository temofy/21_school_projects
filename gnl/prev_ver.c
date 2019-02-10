/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:53:46 by cheller           #+#    #+#             */
/*   Updated: 2019/02/10 15:18:07 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
//#define ft_strdup ft_strdup

/*char	*ft_strtchr(char *s, int c)
{
	char	*str;
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(s))
	{
		if (s[i] == (char)c)
		{
			str = ft_strnew(i);
			str = ft_strncpy(str, s, i);
			return (str);
		}
	}
	return (NULL);
}*/
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

int		check_remainder(t_list_fd *cur_lst, char **line)
{
	char	*tmp;

	if (cur_lst->tmp_line)
	{
		if (ft_isthere_chr(cur_lst->tmp_line, '\n'))
		{
			*line = ft_strtchr(cur_lst->tmp_line, '\n');
			tmp = cur_lst->tmp_line;
			cur_lst->tmp_line = ft_strdup(ft_strpchr(tmp, '\n'));
			free(tmp);
			return (1);
		}
		else
		{
			tmp = *line;
			*line = ft_strdup(cur_lst->tmp_line);
			cur_lst->tmp_line = NULL;
			if (tmp)
				free(tmp);
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
	if (check_remainder(cur_lst, line))
		return (1);
	while (!(cur_lst->tmp_line))
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (bytes == 0 && !(*line) &&!(cur_lst->tmp_line))
			return (0);
		else if (bytes == 0)
			return (1);
		buff[bytes] = '\0';
		if (ft_isthere_chr(buff, '\n'))
		{
			tmp = ft_strtchr(buff, '\n');
			if (*line)
				*line = ft_strjoin(*line, tmp);
			else
				*line = ft_strdup(tmp);
			free(tmp);
			cur_lst->tmp_line = ft_strdup(ft_strpchr(buff, '\n'));
			return (1);
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
		}
	}
	return (1);
}
