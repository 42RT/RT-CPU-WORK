# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/24 13:16:13 by rdieulan          #+#    #+#              #
#    Updated: 2017/01/04 17:38:56 by rdieulan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

LIBFT = libft/libft.a
LIBVEC = libvec/lib_vec.a
GLIB = SDL2/lib/libSDL2.a

SRC = main.c

SRCO = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCO)
	make -C libft
	make -C libvec
	gcc $(FLAG) -c $(SRC)
	gcc -o $(NAME) $(SRCO) $(LIBFT) $(LIBVEC) $(GLIB)

clean:
	make -C libft clean
	make -C libvec clean
	rm -f $(SRCO)

fclean: clean
	make -C libft fclean
	make -C libvec fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
