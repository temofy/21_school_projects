# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaeron-g <aaeron-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/25 20:03:51 by cheller           #+#    #+#              #
#    Updated: 2019/05/30 12:35:48 by aaeron-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = cheks.c ft_printf.c handler_d.c handler_p.c handler_text.c hex.c handler_u.c \
		handler_o.c handler_x.c handler_x_big.c hex_big_staff.c\
		hex_staff.c oct_staff.c handler_f.c long_arithmetic.c handler_b.c represents.c \
		cleanup.c getting.c conversions.c overflow.c rounding.c additional_func.c bin_staff.c \
		handler_unicode.c

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
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all