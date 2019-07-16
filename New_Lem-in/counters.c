#include "lem-in.h"

int 	count_links(char **file, int i)
{
	int		links;

	links = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 1 && ft_isthere_chr(file[i], '-'))
			links++;
		i++;
	}
	/*if (file[i] != NULL)
		return (-1);*/
	return (links);
}

int 	count_rooms(char **file, int i)
{
	int		rooms;

	rooms = 0;
	while (file[i])
	{
		if (ft_count_words(file[i]) == 3 && !ft_isthere_chr(file[i], '#'))
			rooms++;
		i++;
	}
	return (rooms - 2);
}
