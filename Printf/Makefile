# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cheller <cheller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/25 20:03:51 by cheller           #+#    #+#              #
#    Updated: 2019/04/04 15:23:27 by cheller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = cheks.c ft_printf.c handler_d.c handler_p.c handler_text.c hex.c 

LIBFT = libft

OBJ  = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	gcc -c $(SRC) -I.
	make -C LIBFT re
	cp $(LIBFT)/libft.a $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	@rm -f *.o
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all