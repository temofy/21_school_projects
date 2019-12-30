/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:15:56 by cheller           #+#    #+#             */
/*   Updated: 2019/02/03 17:27:45 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int			write_lines(int fd, char *buff, t_list_fd *cur)
{
	int		i;
	int		is_carry;

	is_carry = 0;
	i = -1;
	while ((buff[++i] != '\0' && i != (int)(ft_strlen(buff) - 1)))
		if (buff[i] == '\n' && (!(PENULT_CHR)))
		{
			cur->next_lst = ft_lstnew_fd(fd, ft_strftchr(buff, i + 1, '\n'));
			cur = cur->next_lst;
			is_carry = 2;
		}
	if (ft_strlen(buff) < BUFF_SIZE)
		return (1);
	if (buff[BUFF_SIZE - 1] == '\n')
		return (1);
	return (is_carry);
}

int			read_line(int fd, char *buff, t_list_fd *cur, int is_line)
{
	char	*next_line;
	char	*tmp_line;

	if (is_line == 0 || is_line == 2)
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
	is_line = write_lines(fd, buff, cur);
	if (is_line == 0)
	{
		ft_bzero(buff, BUFF_SIZE);
		return (0);
	}
	free(buff);
	return (is_line == 2) ? 2 : 1;
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
	char				*buff;
	int					bytes;
	static int			is_line;

	is_line = (!is_line || is_line == 1) ? -1 : is_line;
	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	buff = ft_strnew(BUFF_SIZE);
	if (!first_lst)
		first_lst = ft_lstnew_fd(-1, NULL);
	while (is_line != 1)
	{
		if ((bytes = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (bytes != 0)
			is_line = read_line(fd, buff, ft_find_last_lst(first_lst), is_line);
		if (is_line == 2 || bytes == 0)
			break ;
	}
	if ((find_next_line(fd, first_lst)) == NULL)
		return (0);
	*line = ft_strdup((find_next_line(fd, first_lst))->tmp_line);
	free_line(fd, first_lst);
	return (1);
}
