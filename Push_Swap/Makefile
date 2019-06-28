# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/25 20:03:51 by cheller           #+#    #+#              #
#    Updated: 2019/06/24 12:06:52 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PUSH_SWAP_PROGRAM = push_swap

CHECKER_PROGRAM = checker

PS_SRC = instructions.c stack_manipulations.c push_swap.c sorting.c finders.c handler_steps.c handler_sequences.c \
            instr_execution.c

CH_SRC = instructions.c stack_manipulations.c  checker.c

LIBFT = libft

PS_OBJ = $(PS_SRC:.c=.o)

CH_OBJ = $(CH_SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(CHECKER_PROGRAM) $(PUSH_SWAP_PROGRAM)

$(CHECKER_PROGRAM):
	@gcc -c $(FLAGS) $(CH_SRC) -I.
	@make -C LIBFT re
	@gcc $(CH_OBJ) $(LIBFT)/libft.a -o $(CHECKER_PROGRAM)

$(PUSH_SWAP_PROGRAM):
	@gcc -c $(FLAGS) $(PS_SRC) -I.
	@gcc $(PS_OBJ) $(LIBFT)/libft.a -o $(PUSH_SWAP_PROGRAM)

clean:
	@rm -f $(PS_OBJ) $(CH_OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(PUSH_SWAP_PROGRAM) $(CHECKER_PROGRAM)
	@make -C $(LIBFT) fclean

re: fclean all