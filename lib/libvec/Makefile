LIB =		libvec.a
SRC_NAME =	normalize.c \
			dot.c \
			multiply_vec.c \
			sub_vec.c \
			add_vec.c \
			div_vec.c \
			dot_div.c \
			get_inters.c \
			not_vec.c \
			rot.c \
			rotvec.c\
			product_vec.c \
			get_dist.c \
			reflect_vec.c \
			rotx.c \
			roty.c \
			rotz.c \
			calc_vec.c

SRC =		$(addprefix src/, $(SRC_NAME))

OBJ =		$(SRC:.c=.o)

CC =		gcc

CFLAGS = 	-Wall -Werror -Wextra -I ./include

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)
	ranlib $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
