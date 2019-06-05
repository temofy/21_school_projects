#include "libft.h"

size_t		ft_intlen(const unsigned int *nbr)
{
	size_t length;

	length = 0;
	while (nbr[length])
		length++;
	return (length);
}


