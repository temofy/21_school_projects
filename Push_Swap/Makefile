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

PS_SRC = instructions.c stack_manipulations.c push_swap.c new_method.c finders.c handler_steps.c handler_sequences.c

CH_SRC = instructions.c stack_manipulations.c  checker.c

LIBFT = libft

PS_OBJ = instructions.o stack_manipulations.o push_swap.o new_method.o finders.o handler_steps.o handler_sequences.o

CH_OBJ = instructions.o stack_manipulations.o checker.o

FLAGS = -Wall -Wextra -Werror

all: $(CHECKER_PROGRAM) $(PUSH_SWAP_PROGRAM)

$(CHECKER_PROGRAM):
	gcc -c $(CH_SRC) -I.
	make -C LIBFT re
	gcc $(CH_OBJ) $(LIBFT)/libft.a -o $(CHECKER_PROGRAM)

$(PUSH_SWAP_PROGRAM):
	gcc -c $(PS_SRC) -I.
	gcc $(PS_OBJ) $(LIBFT)/libft.a -o $(PUSH_SWAP_PROGRAM)

clean:
	@rm -f $(PS_OBJ) $(CH_OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(PUSH_SWAP_PROGRAM) $(CHECKER_PROGRAM)
	@make -C $(LIBFT) fclean

re: fclean all