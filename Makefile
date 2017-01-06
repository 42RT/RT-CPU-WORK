# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/24 13:16:13 by rdieulan          #+#    #+#              #
#    Updated: 2017/01/06 14:39:49 by rfriscca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

PATH_SRC = srcs/
PATH_LIB = lib/

LIBFT = $(PATH_LIB)libft/libft.a
LIBVEC = $(PATH_LIB)libvec/lib_vec.a
MLX_OSX = $(PATH_LIB)minilibx_macos/libmlx.a
MLX_LINUX = $(PATH_LIB)minilibx/libmlx.a
SDL2 = $(PATH_LIB)SDL2/lib/libSDL2.a

SRC = $(PATH_SRC)main.c\
	  $(PATH_SRC)atof.c\
	  $(PATH_SRC)calc_ncone.c\
	  $(PATH_SRC)calc_ncylinder.c\
	  $(PATH_SRC)camera.c\
	  $(PATH_SRC)color_correction.c\
	  $(PATH_SRC)color.c\
	  $(PATH_SRC)cone.c\
	  $(PATH_SRC)cylinder.c\
	  $(PATH_SRC)default.c\
	  $(PATH_SRC)error.c\
	  $(PATH_SRC)event.c\
	  $(PATH_SRC)ft_new_line.c\
	  $(PATH_SRC)mlx_pixel_put_img.c\
	  $(PATH_SRC)otherfunctions.c\
	  $(PATH_SRC)parse_camera.c\
	  $(PATH_SRC)parse_cone.c\
	  $(PATH_SRC)parse_cylinder.c\
	  $(PATH_SRC)parse_file.c\
	  $(PATH_SRC)parse_plane.c\
	  $(PATH_SRC)parse_sphere.c\
	  $(PATH_SRC)parse_spot.c\
	  $(PATH_SRC)plan.c\
	  $(PATH_SRC)raycaster.c\
	  $(PATH_SRC)save_file.c\
	  $(PATH_SRC)sphere.c\
	  $(PATH_SRC)spot.c\
	  $(PATH_SRC)test_obj.c\
	  $(PATH_SRC)test_spot.c\
	  $(PATH_SRC)trace.c

SRCO = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra
MLX_FLAG = -framework OpenGL -framework Appkit

all: $(NAME)

$(NAME): $(SRCO)
	make -C $(PATH_LIB)libft
	make -C $(PATH_LIB)libvec
	make -C $(PATH_LIB)minilibx_macos
	gcc -o $(NAME) $(SRCO) $(LIBFT) $(LIBVEC) $(MLX_OSX) $(FLAG) $(MLX_FLAG)

linux:
	make -C $(PATH_LIB)libft
	make -C $(PATH_LIB)libvec
	make -C $(PATH_LIB)minilibx
	gcc $(FLAG) $(INCLUDE) -c $(SRC)
	gcc -o $(NAME) $(SRCO) $(LIBFT) $(LIBVEC) $(MLX_LINUX) $(MLX_FLAG)

clean:
	make -C $(PATH_LIB)libft clean
	make -C $(PATH_LIB)libvec clean
	make -C $(PATH_LIB)minilibx_macos
	make -C $(PATH_LIB)minilibx
	rm -f $(SRCO)

fclean: clean
	make -C $(PATH_LIB)libft fclean
	make -C $(PATH_LIB)libvec fclean
	/bin/rm -f $(NAME)

re: fclean all
re_linux : fclean linux

.PHONY: all linux clean fclean re re_linux
