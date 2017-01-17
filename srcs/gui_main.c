/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 14:19:34 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>
# include <rtdefs.h>

void		gui_color_set(t_gui *gui, char *type, char *style)
{
	if (ft_strstr(type, "container") != NULL)
	{
		if (ft_strstr(style, "basic") != NULL)
		{
			gui->color->r = 255;
			gui->color->g = 255;
			gui->color->b = 255;
			gui->color->a = 255;
		}
	}
}

void		gui_build(t_gui	*gui)
{
	gui_background_get_set_n_display(gui);
	gui->cbcnt = 0;
	gui->container = (t_container **)malloc(sizeof(t_container *)
			* DEF_GUI_CONTAINER_TOTAL_NB);
	printf("GUI : Start building container.\n");
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_HEADER);
	gui_build_container(gui, DEF_GUI_DYNAMIC, DEF_GUI_CONTAINER_MIDDLE);
	gui_build_container(gui, DEF_GUI_DYNAMIC, DEF_GUI_CONTAINER_MIDDLE);
	gui_build_container(gui, DEF_GUI_DYNAMIC, DEF_GUI_CONTAINER_MIDDLE);
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_FOOT);
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_FOOT);
	printf("GUI : Container successfully built.\n");
	printf("GUI : Applying Render...\n");
	SDL_RenderPresent(gui->img);
	SDL_DestroyRenderer(gui->img);
}

t_gui		*gui_alloc()
{
	t_gui	*gui;

	if ((gui = (t_gui *)malloc(sizeof(t_gui))) == NULL)
		error(1);
	if ((gui->color = (t_color *)malloc(sizeof(t_color))) == NULL)
		error(1);
	if ((gui->display = (SDL_DisplayMode *)malloc(sizeof(SDL_DisplayMode))) == NULL)
		error(1);
	return (gui);
}

t_gui		*gui_init()
{
	t_gui			*gui;

	printf("\nGUI : Initializing interface....\n");
	gui = gui_alloc();
	if (SDL_GetCurrentDisplayMode(0, gui->display) != 0)
		gui_error(1);
	gui->width = DEF_GUI_WIDTH;
	gui->height = DEF_IMG_HEIGHT;
	gui->anchor_x = (gui->display->w + DEF_IMG_WIDTH) / 2;
	gui->anchor_y = SDL_WINDOWPOS_CENTERED;
	gui->win = SDL_CreateWindow("Tool box", gui->anchor_x, gui->anchor_y,
			gui->width, gui->height, SDL_WINDOW_SHOWN);
	if (gui->win)
		gui->img = SDL_CreateRenderer(gui->win, -1, SDL_RENDERER_SOFTWARE);
	else
		gui_error(4);
	gui->tmp_lim = 0;
	printf("GUI : interface successfully initialized.\n");
	gui_build(gui);
	return (gui);
}
