# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/21 13:24:06 by rfriscca          #+#    #+#              #
#    Updated: 2016/12/15 14:45:11 by rfriscca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
FLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGl -framework AppKit
LIBRARY = -Llibft/ -lft -Lminilibx_macos/ -lmlx
INCLUDES = -I srcs/ -I libft/ -I minilibx_macos/
SRCS_DIR = srcs
MISC_DIR = srcs/misc
OBJECTS_DIR = srcs/objects
PARSER_DIR = srcs/parser
RAYCASTER_DIR = srcs/raycaster
VEC_DIR = srcs/vec_transfo
MAIN = main.c
MISC = atof.c				\
	   color.c				\
	   default.c			\
	   error.c				\
	   ft_new_line.c		\
	   mlx_pixel_put_img.c
OBJECTS = camera.c		\
		  cone.c		\
		  cylinder.c	\
		  plan.c		\
		  sphere.c		\
		  spot.c
PARSER = color_correction.c		\
		 parse_camera.c			\
		 parse_cylinder.c		\
		 parse_plane.c			\
		 parse_spot.c			\
		 otherfunctions.c		\
		 parse_cone.c			\
		 parse_file.c			\
		 parse_sphere.c			\
		 save_file.c
RAYCASTER = event.c			\
			raycaster.c		\
			test_obj.c		\
			test_spot.c		\
			trace.c
VEC = rotation.c		\
	  translation.c		\
	  vec_formula.c		\
	  vec_formula2.c
OBJ = $(MAIN:.c=.o)	\
	$(MISC:.c=.o) 		\
	$(OBJECTS:.c=.o) 	\
	$(PARSER:.c=.o) 	\
	$(RAYCASTER:.c=.o) 	\
	$(VEC:.c=.o)
LIBFT_DIR = libft
MLX_DIR = minilibx_macos

all : LIBFT MLX $(NAME)

LIBFT :
	make -C $(LIBFT_DIR)

MLX :
	make -C $(MLX_DIR)

$(NAME) : $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBRARY) $(INCLUDES) $(FRAMEWORK)

%.o : $(VEC_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

%.o : $(RAYCASTER_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

%.o : $(PARSER_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

%.o : $(OBJECTS_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

%.o : $(MISC_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

%.o : $(SRCS_DIR)/%.c
	gcc $(FLAGS) -c $< $(INCLUDES)

clean :
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re LIBFT MLX
