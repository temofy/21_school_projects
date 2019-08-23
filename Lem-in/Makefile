# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/29 19:38:22 by cheller           #+#    #+#              #
#    Updated: 2019/08/19 16:02:34 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

SRC = lem_in.c reading.c counters.c release.c readers.c starter.c finders.c checkers.c \
        exits_entrances.c handlers.c actions_with_paths.c actions_with_ways.c

LIBFT = libft

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(LEM_IN)

$(LEM_IN):
	@gcc -c $(SRC) -I.
	@make -C LIBFT re
	@gcc $(OBJ) $(LIBFT)/libft.a $(LIBFT)/libftprintf.a -o $(LEM_IN)

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(LEM_IN)
	@make -C $(LIBFT) fclean

re: fclean all