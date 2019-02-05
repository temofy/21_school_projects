#include "get_next_line.h"
//#include <stdio.h>

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
	//ft_putstr("read()\n");
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
		{
			//ft_putstr("done\n");
			read_line(fd, fd_list, buff);
		}
		return (1);
	}
	fd_list = ft_find_last_lst(fd_list);
	//printf("buff: %s\n", buff);
	fd_list->next_lst = ft_lstnew_fd(fd, ft_strdup(buff));
	fd_list = fd_list->next_lst;
	//ft_putstr("this done\n");
	//printf("line: %s", fd_list->tmp_line);
	if (!(ft_isthere_chr(fd_list->tmp_line, '\n')))
	{
		//ft_putstr("done\n");
		read_line(fd, fd_list, buff);
	}
	return (1);
}
/*char 	*ft_strmchr(char *s, int c)
{
	int	found_chr;
	char	*str;

	str = s;
	found_chr = 0;
	while (*s)
	{
		if (*str == (char)c)
			found_chr = 1;
		else if (*str != (char)c && found_chr)
			return (str);
		str++;
	}
	return (s);
}*/

int	get_next_line(const int fd, char **line)
{
	static t_list_fd	*fd_lists;
	char			*buff;
	int 			rtn;
	char			*tmp;
	t_list_fd		*cur_lst;

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	buff = ft_strnew(BUFF_SIZE);
	if (!fd_lists)
		fd_lists = ft_lstnew_fd(-1, NULL);
	rtn = read_line(fd, fd_lists, buff); //цикл
	//printf("rtn: %d\n", rtn);
	cur_lst = find_lst(fd, fd_lists);
	/*int i = -1;
	printf("tmp_line: ");
	while ((cur_lst->tmp_line)[++i] != '\0')
		printf("%d|", (cur_lst->tmp_line)[i]);
	printf("\nтут\n");*/
	if ((!(cur_lst->tmp_line) || !(ft_strlen(cur_lst->tmp_line))) && !rtn)
		return (0);
	tmp = ft_strtchr(cur_lst->tmp_line, '\n');
	*line = tmp;
	tmp  = cur_lst->tmp_line;
	cur_lst->tmp_line = ft_strdup((ft_strchr(cur_lst->tmp_line, '\n')) + 1);
	//printf("reminder: %s\n", cur_lst->tmp_line);
	free(tmp);
	free(buff);
	return (1);
}
