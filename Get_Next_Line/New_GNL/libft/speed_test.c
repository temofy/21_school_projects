#define MOLIBYTES 235436
#include <stdio.h>
#include <time.h>
#include "../get_next_line.h"
#include <fcntl.h>

int main()
{
    fopen("data", "w");
    clock_t start, end;
    double cpu_time_used;
		char	*dup;

    start = clock();
    int fd;
    char *test_str = malloc(MOLIBYTES + 1);
   //char *line;
    //char check[MOLIBYTES];
    for (int i = 0; i < MOLIBYTES; ++i)
		{
			if (i%2==0)
        test_str[i] = 'i';
			else
				test_str[i]='\n';
		}
    test_str[MOLIBYTES] = '\0';
    fd = open("data", O_RDWR);
    write(fd, test_str, MOLIBYTES + 1);
    /*read(fd, check, MOLIBYTES);
    close(fd);*/
    fd = open("data", O_RDONLY);
		printf("here\n");
		dup = ft_strdup(test_str);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time: %lf seconds", cpu_time_used);
}
