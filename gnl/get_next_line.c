/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:53:46 by cheller           #+#    #+#             */
/*   Updated: 2019/02/13 14:52:01 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		//printf("len: %d\n", len);
		while (cur_lst->tmp_line[i] != '\n' && cur_lst->tmp_line[i] != '\0')
			i++;
		if (i < len)
		{
			//printf("i: %d\n", i);
			tmp = cur_lst->tmp_line;
			*line = ft_strsub(tmp, 0, i);
			//printf("line: %s\n", *line);
			cur_lst->tmp_line = ft_strsub(tmp + i + 1, 0, len - i);
			//printf("cur_lst: %s\n", cur_lst->tmp_line);
			free(tmp);
			return (1);
		}
		else if (i == len)
		{
			//printf("tmp_line: %s\n", cur_lst->tmp_line);
			if (i != 0)
			{
				//printf("сука\n");
				*line = ft_strsub(cur_lst->tmp_line, 0, len);
				//*line = ft_strjoin("", cur_lst->tmp_line);
				//printf("line: %s\n", *line);
			}
			//printf("free\n");
			ft_strdel(&cur_lst->tmp_line);
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
	//free(*line);
	*line = ft_strnew(0);
	tmp = NULL;
	if (!fd_lists)
		if(!(fd_lists = ft_lstnew_fd(fd, NULL)))
			return (-1);
	if (!(cur_lst = find_lst(fd, fd_lists)))
		return (-1);
	if (check_remainder(cur_lst, line))
		return (1);
	while (!(cur_lst->tmp_line))
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (bytes == 0 && !(cur_lst->tmp_line))
		{
			free(*line);
			return (free_lst(fd, fd_lists));
		}
		else if (bytes == 0)
			return (1);
		buff[bytes] = '\0';
		if (ft_strchr(buff, '\n'))
		{
			if(!(tmp = ft_strtchr(buff, '\n')))
				return (-1);
			*line = ft_strjoin(*line, tmp);
			cur_lst->tmp_line = ft_strdup(ft_strpchr(buff, '\n'));
			free(tmp);
			break ;
		}
		/*printf("*line: %s\n", *line);
		if (ft_strlen(*line))
		{*/
			tmp = *line;
			if(!(*line = ft_strjoin(*line, buff)))
				return (-1);
			free(tmp);
		//}
		/*else
			if(!(*line = ft_strdup(buff)))
				return (-1);*/
	}
	return (1);
}
