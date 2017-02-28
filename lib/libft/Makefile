#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 13:05:55 by jrouilly          #+#    #+#              #
#    Updated: 2014/01/29 09:07:40 by jrouilly         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -I ./includes
NAME =	libft.a

SRC =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
		ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
		ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
		ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
		ft_itoa.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putendl.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
		ft_get_next_line.c ft_strnclr.c ft_newstrcat.c ft_printf.c \
		ft_puthex.c ft_hextoa.c ft_readfile.c ft_getfile.c ft_strndup.c \
		ft_strdup_trim.c ft_strlen_trim.c ft_abs.c ft_putfloat.c ft_atof.c \
		ft_strlen_trim2.c ft_ishex.c ft_hexval.c ft_hextoi.c ft_strcchr.c \
		ft_concat.c ft_lstadd.c ft_lstdelone.c ft_lstnew.c

OBJ =	ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
		ft_memchr.o ft_memcmp.o ft_strlen.o ft_strdup.o ft_strcpy.o \
		ft_strncpy.o ft_strcat.o ft_strncat.o ft_strlcat.o ft_strchr.o \
		ft_strrchr.o ft_strstr.o ft_strnstr.o ft_strcmp.o ft_strncmp.o \
		ft_atoi.o ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o \
		ft_isprint.o ft_toupper.o ft_tolower.o \
		ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strclr.o \
		ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o \
		ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o \
		ft_itoa.o ft_putchar.o ft_putstr.o ft_putnbr.o ft_putendl.o \
		ft_putchar_fd.o ft_putstr_fd.o ft_putnbr_fd.o ft_putendl_fd.o \
		ft_get_next_line.o ft_strnclr.o ft_newstrcat.o ft_printf.o \
		ft_puthex.o ft_hextoa.o ft_readfile.o ft_getfile.o ft_strndup.o \
		ft_strdup_trim.o ft_strlen_trim.o ft_abs.o ft_putfloat.o ft_atof.o \
		ft_strlen_trim2.o ft_ishex.o ft_hexval.o ft_hextoi.o ft_strcchr.o \
		ft_concat.o ft_lstadd.o ft_lstdelone.o ft_lstnew.o

all: $(NAME)
	@echo SUCCESS > /dev/null

$(NAME) :
	@echo "\033[34mCompiling libft : \033[31m"
	@gcc $(CFLAGS) $(LDFLAGS) -c $(SRC) > /dev/null
	@ar r $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[1;32mLibft Compiled !\033[0m"

clean:
	@rm -f $(OBJ)
	@echo "\033[34mLibft cleaned (OBJ only)\033[0m"

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[34mLibft cleaned (All)\033[0m"

re: fclean all
