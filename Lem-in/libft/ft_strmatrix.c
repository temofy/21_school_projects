#include "libft.h"

char	**ft_strmatrix(int m, int n)
{
	char	**matrix;
	int 	i;

	i = 0;
	if (n < 1 && m < 1)
		return (NULL);
	matrix = malloc(sizeof(char**) * (m + 1));
	while (i < m)
	{
		matrix[i] = ft_strnew(n);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
