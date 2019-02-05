# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/31 15:07:13 by cheller           #+#    #+#              #
#    Updated: 2019/02/05 16:58:43 by qweissna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = fillit.c validation.c prints.c

OBJ = fillit.o validation.o

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRC) fillit.h
	gcc  libft/libft.a $(SRC) -o $(NAME)
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
