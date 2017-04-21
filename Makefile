#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/03/15 01:15:01 by jrouilly          #+#    #+#              #
#    Updated: 2017/03/29 13:32:26 by rfriscca         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = raytracer

PATH_SRC =		srcs/
PATH_GFX =		$(PATH_SRC)gfx/
PATH_GUI =		$(PATH_SRC)gui/
PATH_PARSER =	$(PATH_SRC)parser/
PATH_LIB =		lib/
UNAME_S =		$(shell uname -s)
THREADS =		$(shell grep -c ^processor /proc/cpuinfo)

INCLUDES =		-I lib/libft/includes -I lib/libvec/include -I includes
CFLAGS =		-Wall -Wextra -Werror
LDFLAGS =		-lm -L ./$(PATH_LIB)libft -lft -L ./$(PATH_LIB)libvec -lpthread

SRC =		$(PATH_PARSER)parse.c \
			$(PATH_PARSER)parse_file.c \
			$(PATH_PARSER)parse_light.c \
			$(PATH_PARSER)parse_obj.c \
			$(PATH_PARSER)parse_obj_utils.c \
			$(PATH_PARSER)parse_settings.c \
			$(PATH_PARSER)parse_settings_utils.c \
			$(PATH_PARSER)parse_utils.c \
			$(PATH_PARSER)parse_utils_2.c \
			$(PATH_GFX)gfx.c \
			$(PATH_GFX)gfx_image.c \
			$(PATH_GFX)gfx_pixel.c \
			$(PATH_GFX)gfx_utils.c \
			$(PATH_SRC)main.c \
			$(PATH_SRC)ft_err.c \
			$(PATH_SRC)anti_aliasing.c \
			$(PATH_SRC)display.c \
			$(PATH_SRC)ft_aff.c \
			$(PATH_SRC)event.c \
			$(PATH_SRC)expose_hook.c \
			$(PATH_SRC)loading.c \
			$(PATH_SRC)console.c \
			$(PATH_SRC)cone.c \
			$(PATH_SRC)cylinder.c \
			$(PATH_SRC)dfloor.c \
			$(PATH_SRC)disk.c \
			$(PATH_SRC)floor.c \
			$(PATH_SRC)sphere.c \
			$(PATH_SRC)square.c \
			$(PATH_SRC)new_light.c \
			$(PATH_SRC)new_obj.c \
			$(PATH_SRC)new_settings.c \
			$(PATH_SRC)aff_light.c \
			$(PATH_SRC)aff_obj.c \
			$(PATH_SRC)aff_settings.c \
			$(PATH_SRC)reload.c \
			$(PATH_SRC)bmp.c \
			$(PATH_SRC)utils.c \
			$(PATH_SRC)utils_2.c \
			$(PATH_SRC)hdr_colors.c \
			$(PATH_SRC)hdr_colors_convert.c \
			$(PATH_SRC)color_utils.c \
			$(PATH_SRC)copy_utils.c \
			$(PATH_SRC)get_utils.c \
			$(PATH_SRC)obj_utils.c \
			$(PATH_SRC)thread_utils.c \
			$(PATH_SRC)vec_utils.c \
			$(PATH_SRC)vec_utils_2.c \
			$(PATH_SRC)vec_utils_3.c \
			$(PATH_SRC)trace_lights.c \
			$(PATH_SRC)compose.c \
			$(PATH_SRC)cube.c \
			$(PATH_SRC)other_primitive.c \
			$(PATH_SRC)procedural.c \
			$(PATH_SRC)error.c \
			$(PATH_SRC)glass.c \
			$(PATH_GUI)gui_error.c \
			$(PATH_GUI)gui_tool.c \
			$(PATH_GUI)gui_refresher.c \
			$(PATH_GUI)gui_widget_tool.c \
			$(PATH_GUI)gui_background.c \
			$(PATH_GUI)gui_button.c \
			$(PATH_GUI)gui_textbox.c \
			$(PATH_GUI)gui_scroll.c \
			$(PATH_GUI)gui_gauge.c \
			$(PATH_GUI)gui_freetxt.c \
			$(PATH_GUI)gui_help.c \
			$(PATH_GUI)gui_param.c \
			$(PATH_GUI)gui_param_checkbox.c \
			$(PATH_GUI)gui_param_button.c \
			$(PATH_GUI)gui_main.c \
			$(PATH_GUI)gui_ttf.c \
			$(PATH_GUI)gui_parse.c \
			$(PATH_GUI)gui_parse_param.c \
			$(PATH_GUI)gui_parse_main.c \
			$(PATH_GUI)gui_apply.c \
			$(PATH_GUI)gui_reset.c \
			$(PATH_GUI)gui_save.c \
			$(PATH_GUI)gui_pixel_put.c \
			$(PATH_GUI)gui_event.c \
			$(PATH_GUI)gui_event_textbox.c \
			$(PATH_GUI)gui_event_textbox_2.c \
			$(PATH_GUI)gui_event_textbox_3.c

ifeq ($(UNAME_S),Darwin)
	INC 	+=	-I ~/.brew/Cellar/sdl2/2.0.5/include/SDL2 \
				-I ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2
	LDFLAGS +=	-L ~/.brew/Cellar/sdl2/2.0.5/lib -lSDL2 \
				-L ~/.brew/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf
else ifeq ($(UNAME_S),Linux)
	LDFLAGS +=	-lSDL2 -lSDL2_ttf
endif

OBJ = $(SRC:.c=.o)

CFLAGS += $(INCLUDES)

all:
	@make -s -j$(THREADS) $(NAME)

$(NAME) : $(OBJ)
	@make -C $(PATH_LIB)libft > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec > /dev/null 2>&1
	@echo "\033[34mCompiling $(NAME) : \033[0m"
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "\033[1;32m$(NAME) Compiled !\n\033[0m"

clean:
	@make -C $(PATH_LIB)libft clean > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec clean > /dev/null 2>&1
	@rm -f $(OBJ)
	@echo "\033[34m$(NAME) cleaned (OBJ only)\033[0m"

fclean:
	@make -C $(PATH_LIB)libft fclean > /dev/null 2>&1
	@make -C $(PATH_LIB)libvec fclean > /dev/null 2>&1
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "\033[34m$(NAME) cleaned (All)\n\033[0m"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@ $(INC) 2>&1

re:			fclean all

debug:		fclean
	@make -C libft/ re > /dev/null
	@echo "\033[34mCompiling $(NAME) (debug mode): \033[0m"
	@gcc -g $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LDFLAGS)
	@echo "\033[1;32m$(NAME) Compiled ! (debug mode)\n\033[0m"

