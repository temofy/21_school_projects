#ifndef VIRTUAL_HEADER_H
# define VIRTUAL_HEADER_H

# include "../libft/Headers/libft.h"
# include "op.h"

typedef struct	s_player
{
	int			identifier;
	char		*name;
	char		*comment;
	int			code_size;
	char		*code;
}				t_player;

typedef struct	s_player_nbr
{
	int 	index_file;
	int 	identifier;
}				t_plr_nbr;

typedef struct	s_flags
{
	int 		dump;
	int 		vis;
	int			*order_idtfrs;
	int 		amount_players;
	t_plr_nbr	*plr_nbr;
}				t_flags;

t_player		*g_players;

int		virual_machine(int amount_players, char **files_champoins);
void	print_hex_data(int argc, char **argv);
int		parsing_arguments(int argc, char **argv, t_flags *flags);
int 	ft_is_strdigit(char *str);

#endif
