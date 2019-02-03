/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:15:56 by cheller           #+#    #+#             */
/*   Updated: 2019/02/03 19:31:29 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define ft_strdup strdup
#define ft_bzero bzero

void		free_line(int fd, t_list_fd *first_lst)
{
	t_list_fd	*prev_lst;
	t_list_fd	*next_lst;

	prev_lst = first_lst;
	next_lst = first_lst->next_lst;
	while (next_lst)
	{
		if (fd == next_lst->fd)
		{
			if (next_lst->next_lst)
				prev_lst->next_lst = next_lst->next_lst;
			else
				prev_lst->next_lst = NULL;
			free(next_lst->tmp_line);
			free(next_lst);
			return ;
		}
		prev_lst = next_lst;
		next_lst = next_lst->next_lst;
	}
}

void		write_lines(int fd, char *buff, t_list_fd *cur)
{
	int		i;

	i = -1;
	while ((buff[++i] != '\0' && i != (int)(ft_strlen(buff) - 1)))
		if (buff[i] == '\n' && (!(PENULT_CHR)))
		{
			cur->next_lst = ft_lstnew_fd(fd, ft_strftchr(buff, i + 1, '\n'));
			cur = cur->next_lst;
		}
}

int			read_line(int fd, char *buff, t_list_fd *cur, int is_line)
{
	char	*next_line;
	char	*tmp_line;

	if (is_line == 0)
	{
		tmp_line = cur->tmp_line;
		next_line = ft_strftchr(buff, 0, '\n');
		cur->tmp_line = ft_strjoin(tmp_line, next_line);
		free(next_line);
		free(tmp_line);
	}
	else
	{
		cur->next_lst = ft_lstnew_fd(fd, ft_strftchr(buff, 0, '\n'));
		cur = cur->next_lst;
	}
	write_lines(fd, buff, cur);
	if (buff[BUFF_SIZE - 1] != '\n')
	{
		ft_bzero(buff, BUFF_SIZE);
		return (0);
	}
	ft_bzero(buff, BUFF_SIZE);
	return (1);
}

t_list_fd	*find_next_line(int fd, t_list_fd *first_lst)
{
	t_list_fd	*next_line;

	next_line = first_lst;
	while (next_line)
	{
		if (next_line->fd != fd)
			next_line = next_line->next_lst;
		else
			return (next_line);
	}
	return (NULL);
}

int			get_next_line(const int fd, char **line)
{
	static t_list_fd	*first_lst;
	char			*buff;
	int					bytes;
	int					is_line;

	is_line = -1;
	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	buff = ft_strnew(BUFF_SIZE);
	if (!first_lst)
		first_lst = ft_lstnew_fd(-1, NULL);
	while (is_line < 1)
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		else if (bytes == 0)
			break ;
		is_line = read_line(fd, buff, ft_find_last_lst(first_lst), is_line);
	}
	free(buff);
	if ((find_next_line(fd, first_lst)) == NULL)
		return (0);
	*line = ft_strdup((find_next_line(fd, first_lst))->tmp_line);
	free_line(fd, first_lst);
	return (1);
}
