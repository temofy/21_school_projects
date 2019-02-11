/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 17:48:21 by cheller           #+#    #+#             */
/*   Updated: 2019/02/03 19:28:49 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "cheller/get_next_line.h"

int		main(int argc, char **argv)
 {
	int		fd;
	ssize_t	ret;
	char			ch[BUFF_SIZE];
	char			*line;

	line = NULL;
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Cannot open file\n");
		return (0);
	}
	int rtn = 1;
	/*rtn =  get_next_line(fd, &line);
	printf("\nReady line: %s\n", line);
	rtn =  get_next_line(fd, &line);
	printf("\nReady line: %s\n", line);
*/
	while ((rtn = get_next_line(fd, &line)))
	{
		//printf("\nReady line: %s\n", line);
		//printf("return: %d\n", rtn);*/
		printf("%s\n", line);
		free(line);
	}
	if (ret < 0)
		printf("Cannot read file\n");
	close(fd);
	return (0);
}
