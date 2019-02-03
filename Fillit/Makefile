# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 15:07:13 by cheller           #+#    #+#              #
#    Updated: 2019/01/31 15:39:43 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = fillit.c

OBJ = fillit.o

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRC) fillit.h
	gcc  libft/libft.a $(SRC) -o $(NAME)
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
