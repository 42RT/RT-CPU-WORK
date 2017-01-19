# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/24 13:16:13 by rdieulan          #+#    #+#              #
#    Updated: 2017/01/17 16:50:05 by rdieulan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT

PATH_SRC =	srcs/
PATH_LIB =	lib/
UNAME_S =	$(shell uname -s)

INCLUDES =	-I lib/libft/includes -I lib/libvec/include -I include
CFLAGS =	-Wall -Werror -Wextra
LDFLAGS =	-lm -L ./lib/libft -lft -L ./lib/libvec -l_vec
FRAMEWORK =

SRC =	$(PATH_SRC)main.c \
		$(PATH_SRC)atof.c \
		$(PATH_SRC)calc_ncone.c \
		$(PATH_SRC)calc_ncylinder.c \
		$(PATH_SRC)camera.c \
		$(PATH_SRC)color_correction.c \
		$(PATH_SRC)color.c \
		$(PATH_SRC)cone.c \
		$(PATH_SRC)cylinder.c \
		$(PATH_SRC)default.c \
		$(PATH_SRC)error.c \
		$(PATH_SRC)event.c \
		$(PATH_SRC)ft_new_line.c \
		$(PATH_SRC)pixel_put.c \
		$(PATH_SRC)otherfunctions.c \
		$(PATH_SRC)old_parse_camera.c \
		$(PATH_SRC)old_parse_cone.c \
		$(PATH_SRC)old_parse_cylinder.c \
		$(PATH_SRC)old_parse_file.c \
		$(PATH_SRC)old_parse_plane.c \
		$(PATH_SRC)old_parse_sphere.c \
		$(PATH_SRC)old_parse_spot.c \
		$(PATH_SRC)plan.c \
		$(PATH_SRC)raycaster.c \
		$(PATH_SRC)save_file.c \
		$(PATH_SRC)sphere.c \
		$(PATH_SRC)spot.c \
		$(PATH_SRC)test_obj.c \
		$(PATH_SRC)test_spot.c \
		$(PATH_SRC)trace.c \
		$(PATH_SRC)color_utils.c \
		$(PATH_SRC)utils.c \
		$(PATH_SRC)gui_error.c \
		$(PATH_SRC)gui_background.c \
		$(PATH_SRC)gui_container.c \
		$(PATH_SRC)gui_button.c \
		$(PATH_SRC)gui_main.c \
		$(PATH_SRC)gui_ttf.c \
		$(PATH_SRC)parse.c \
		$(PATH_SRC)parse_settings.c \
		$(PATH_SRC)parse_settings_utils.c \
		$(PATH_SRC)parse_utils.c \
		$(PATH_SRC)parse_utils_2.c \
		$(PATH_SRC)parse_file.c \
		$(PATH_SRC)parse_obj.c \
		$(PATH_SRC)parse_obj_utils.c \
		$(PATH_SRC)parse_light.c \
		$(PATH_SRC)get_utils.c \
		$(PATH_SRC)new_obj.c \
		$(PATH_SRC)new_settings.c \
		$(PATH_SRC)new_light.c \
		$(PATH_SRC)compose.c \
		$(PATH_SRC)create_plan_compose.c \
		$(PATH_SRC)create_sphere_compose.c \
		$(PATH_SRC)procedural_textures.c \
		$(PATH_SRC)aff_settings.c

OBJ =	$(SRC:.c=.o)

ifeq ($(UNAME_S),Darwin)
	INCLUDES +=	-I ~/.brew/include/SDL2
	LDFLAGS +=	-L ~/.brew/lib -lSDL2 -lSDL2_ttf
else ifeq ($(UNAME_S),Linux)
	LDFLAGS +=	-lSDL2 -lSDL2_ttf
endif

CFLAGS += $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(PATH_LIB)libft > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec > /dev/null 2>&1
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(FRAMEWORK)
	@echo "\033[1;32m$(NAME) Compiled !\033[0m"

clean:
	@make -C $(PATH_LIB)libft clean > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec clean > /dev/null 2>&1
	@rm -f $(OBJ)
	@echo "\033[31mclean\033[0m"

fclean:
	@make -C $(PATH_LIB)libft fclean > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec fclean > /dev/null 2>&1
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[31mfclean\033[0m"

re: fclean all

.PHONY: all clean fclean re
