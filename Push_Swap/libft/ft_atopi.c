#include "libft.h"

long 	*ft_atopi(const char *str)
{
	long	result;
	long	*p_result;
	int		i;
	int		sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		   || str[i] == '\f' || str[i] == ' ')
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (NULL);
		result = result * 10;
		result += str[i] - '0';
		i++;
	}
	result = result * sign;
	return (p_result = &result);
}
