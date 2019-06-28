/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <cheller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:07:18 by cheller           #+#    #+#             */
/*   Updated: 2019/02/13 15:43:03 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			free_lst(int fd, t_list_fd *first_lst)
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

t_list_fd	*find_lst(int fd, t_list_fd *fd_list)
{
	t_list_fd	*begin;

	begin = fd_list;
	while (fd_list)
	{
		if (fd_list->fd == fd)
			return (fd_list);
		fd_list = fd_list->next_lst;
	}
	begin = ft_find_last_lst(begin);
	begin->next_lst = ft_lstnew_fd(fd, NULL);
	return (begin->next_lst);
}

void		concatenate_lines(t_list_fd *cur_lst, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(cur_lst->tmp_line, buff);
	free(cur_lst->tmp_line);
	cur_lst->tmp_line = tmp;
}

int			write_lines(t_list_fd *cur_lst, char **line)
{
	char	*tmp;
	int		length;

	length = ft_strposchr(cur_lst->tmp_line, '\n');
	if ((cur_lst->tmp_line)[length] == '\n')
	{
		*line = ft_strsub(cur_lst->tmp_line, 0, length);
		tmp = ft_strdup(cur_lst->tmp_line + length + 1);
		free(cur_lst->tmp_line);
		cur_lst->tmp_line = tmp;
		if ((cur_lst->tmp_line)[0] == '\0')
			ft_strdel(&cur_lst->tmp_line);
	}
	else
	{
		*line = ft_strdup(cur_lst->tmp_line);
		ft_strdel(&cur_lst->tmp_line);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char				buff[BUFF_SIZE + 1];
	int					bytes;
	t_list_fd			*cur_lst;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(fd, NULL);
	cur_lst = find_lst(fd, fd_lists);
	while ((bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (cur_lst->tmp_line == NULL)
			cur_lst->tmp_line = ft_strnew(1);
		concatenate_lines(cur_lst, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes == -1)
		return (-1);
	else if (bytes == 0 && !(cur_lst->tmp_line))
		return (free_lst(fd, fd_lists));
	return (write_lines(cur_lst, line));
}
