#include "virtual_header.h"

int 	ft_is_strdigit(char *str)
{
	if (!str || *str == '\0')
		return (-1);
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int 	*init_int_array(int size, int nbr)
{
	int *array;
	int i;

	i = -1;
	array = (int*)malloc(sizeof(int) * size);

	while (++i < size)
		array[i] = nbr;
	return (array);
}
int 	check_file(char *argument)
{
	int i;
	int flag_dot;
	char *extansion;

	extansion = "cor";
	flag_dot = 0;
	i = -1;
	while (argument[++i])
	{
		if (argument[i] == '.')
			flag_dot = 1;
		else if (flag_dot == 1)
		{
			if (argument[i] == *extansion)
			{
				extansion++;
				if (!(*extansion))
					flag_dot = 2;
			}
			else
				return (-1);
		}
		else if (flag_dot == 2)
			return (-1);
	}
	if (flag_dot == 2)
		return (1);
	return (flag_dot == 1) ? -1 : 0;
}

int 	handler_n(int nbr, t_flags *flags, int index)
{
	if (nbr < 1 || nbr > MAX_PLAYERS)
		return (-1);
	if (flags->order_idtfrs[nbr - 1] == 0)
	{
		flags->plr_nbr[nbr - 1].identifier = nbr;
		flags->plr_nbr[nbr - 1].index_file = index;
		flags->order_idtfrs[nbr - 1] = 1;
	}
	else
		return (-1);
	return (1);
}

int		check_flags(int argc, char **argv, int *i, t_flags *flags)
{
	int rtn;

	rtn = -1;
	if (ft_strcmp("-dump", argv[*i]) == 0)
	{
		if (*i + 1 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1)
			{
				flags->dump = ft_atoi(argv[*i + 1]);
				*i += 1;
			}
	}
	else if (ft_strcmp("-n", argv[*i]) == 0)
	{
		if (*i + 2 != argc)
			if (ft_is_strdigit(argv[*i + 1]) == 1 && check_file(argv[*i + 2]) == 1)
			{
				rtn = handler_n(ft_atoi(argv[*i + 1]), flags, *i);
				*i += 2;
			}
	}
	else if (ft_strcmp("-v", argv[*i]) == 0)
		flags->vis = 1;
	return (rtn);
}

int		parsing_arguments(int argc, char **argv, int *amt_pls, t_flags *flags)
{
	int	i;
	int res;

	i = 0;
	res = -1;
	while (++i < argc)
	{
		res = check_file(argv[i]);
		if (res == -1)
			write(1, "Invalid file name", 17);
		else if (res == 1)
		{
			(*amt_pls)++;
			continue;
		}
		else
			res = check_flags(argc, argv, &i, flags);
	}
	return (res);
}
int 	check_unattached_index(int index, t_plr_nbr *plr_nbr)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (plr_nbr[i].index_file == index)
			return (0);
	}
	return (1);
}

int 	find_unattached_file(t_flags *flags, char **argv, int argc)
{
	static int i = 0;

	while (++i < argc)
	{
		if (ft_strstr(argv[i], ".cor") && check_unattached_index(i, flags->plr_nbr))
			return (i);
	}
	return (0);
}

void	set_identifiers(int amount_players, t_flags *flags, int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < amount_players)
	{
		if (flags->order_idtfrs[i] == 0)

	}
}

void	initialize_flags(t_flags *flags)
{
	int i;

	i = -1;
	flags->dump = -1;
	flags->vis = -1;
	flags->plr_nbr = malloc(sizeof(t_plr_nbr) * MAX_PLAYERS);
	while (++i < MAX_PLAYERS)
	{
		flags->plr_nbr[i].index_file = 0;
		flags->plr_nbr[i].identifier = 0;
	}
}

int		main(int argc, char *argv[])
{
	int			amount_players;
	t_flags		flags;

	amount_players = 0;
	if (argc < 2)
	{
		//usage
		return (1);
	}
	else
	{
		initialize_flags(&flags);
		parsing_arguments(argc, argv, &amount_players, &flags);
		if (amount_players > MAX_PLAYERS)
		{
			write(1, "Too many champions\n", 19);
			return (2);
		}
		//virual_machine(argc, argv);
		free(flags.plr_nbr);
	}
	return (0);
}
