/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:58:29 by cheller           #+#    #+#             */
/*   Updated: 2019/03/12 17:46:08 by cheller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_atoi(char *str)
{
	int		nbr;
	int		negative;

	nbr = 0;
	negative = 0;
	while (*str == '\t' || *str == ' ' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = 1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (negative)
		nbr *= -1;
	return (nbr);
}

void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr < 10)
	{
		c = nbr + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		c = (nbr % 10) + '0';
		write(1, &c, 1);
	}
}

int		main(int argc, char *argv[])
{
	int		nbr;
	int		i;

	i = 0;
	if (argc != 2)
		write(1, "\n", 1);
	else
	{
		nbr = ft_atoi(argv[1]);
		if (nbr < 0)
			nbr *= -1;
		while (++i <= 9)
		{
			ft_putnbr(i);
			write(1, " x ", 3);
			ft_putnbr(nbr);
			write(1, " = ", 3);
			ft_putnbr(nbr * i);
			write(1, "\n", 1);
		}
	}
	return (1);
}
