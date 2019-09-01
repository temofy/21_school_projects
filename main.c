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

void	set_identifiers(t_flags *flags, int argc, char **argv)
{
	int i;

	i = -1;
	while (++i < flags->amount_players)
	{
		if (flags->order_idtfrs[i] == 0)
		{
			flags->plr_nbr[i].index_file = find_unattached_file(flags, argv, argc);
			flags->plr_nbr[i].identifier = i + 1;
		}
	}
}

void	initialize_flags(t_flags *flags)
{
	int i;

	i = -1;
	flags->dump = -1;
	flags->vis = -1;
	flags->order_idtfrs = init_int_array(MAX_PLAYERS, 0);
	flags->plr_nbr = malloc(sizeof(t_plr_nbr) * MAX_PLAYERS);
	flags->amount_players = 0;
	while (++i < MAX_PLAYERS)
	{
		flags->plr_nbr[i].index_file = 0;
		flags->plr_nbr[i].identifier = 0;
	}
}

int		main(int argc, char *argv[])
{
	t_flags		flags;
	char		**player_files;
	int 		i;

	if (argc < 2)
	{
		//usage
		return (1);
	}
	else
	{
		initialize_flags(&flags);
		parsing_arguments(argc, argv, &flags);
		if (flags.amount_players > MAX_PLAYERS)
		{
			write(1, "Too many champions\n", 19);
			return (2);
		}
		set_identifiers(&flags, argc, argv);
		player_files = (char**)malloc(sizeof(char*) * flags.amount_players);
		i = -1;
		while (++i < flags.amount_players)
			player_files[i] = argv[flags.plr_nbr[i].index_file];
		//virual_machine(argc, argv);
		free(flags.plr_nbr);
		free(flags.order_idtfrs);
		free(player_files);
	}
	return (0);
}
