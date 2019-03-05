# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <cheller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 15:07:13 by cheller           #+#    #+#              #
#    Updated: 2019/02/24 13:35:18 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIB = libft
INC = fillit.h
SRC = fillit.c validation.c prints.c find_vertices.c free.c ft_lists.c changing_lists.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) fillit.h
	@make -C $(LIB)
	@gcc -c $(FLAGS) $(SRC) -I$(INC)
	@gcc libft/libft.a $(SRC) -o $(NAME)
	@make fclean -C $(LIB)

%.o: %.c fillit.h
	@gcc -c $(FLAGS) $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
