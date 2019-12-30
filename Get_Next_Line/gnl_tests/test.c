#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_isthere_chr(char *s, int c);

int main(int argc, char **argv)
{
	int fd;
	char buf[] = "Artem\nSavchenkov\nAnatolevichZ";
	char buff[10];
	int n;
	char *str;
	int	i = -1;

	fd = open (argv[1], O_RDONLY);
	while ((n = read(fd, buff, 10)) > 0)
	{
		printf("bytes: %d\n", n);
		while (++i != n)
		{	
			printf("buff[%d] = %d\n", i, (int)buff[i]);
			if (buff[i] == '\r')
				printf("Присутствует коретка\n");
		}
		
	}
	str = ft_strftchr(buf, 0, '\n');
	printf("str: %s\n", str);
	printf("buf: %s\n", buf);
	printf("Is there chr: %d", ft_isthere_chr(buf, 'Z'));
	return (0);
}
