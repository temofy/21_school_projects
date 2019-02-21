# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <cheller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 15:07:13 by cheller           #+#    #+#              #
#    Updated: 2019/02/20 15:42:25 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = fillit.c validation.c prints.c find_vertices.c

OBJ = fillit.o validation.o prints.o find_vertices.c

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRC) fillit.h
	gcc libft/libft.a $(SRC) -o $(NAME)
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
