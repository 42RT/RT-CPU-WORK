/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>
# include <rtdefs.h>

t_gui		*get_gui(void)
{
	static	t_gui gui;

	return (&gui);
}

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
	printf("GUI : \033[33mBUILDING CONTENT ...\033[0m\n");
	gui_background_get_set_n_display(gui);
	gui->cbcnt = 0;
	gui->container = (t_container **)malloc(sizeof(t_container *)
			* DEF_GUI_CONTAINER_TOTAL_NB);
	printf("GUI : \033[33mContainer \033[0m: ");
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_HEADER);
	gui_build_container(gui, DEF_GUI_DYNAMIC, DEF_GUI_CONTAINER_MIDDLE);
	gui_build_container(gui, DEF_GUI_DYNAMIC, DEF_GUI_CONTAINER_MIDDLE);
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_HEADER);
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_FOOT);
	gui_build_container(gui, DEF_GUI_CONSTANT, DEF_GUI_CONTAINER_FOOT);
	printf("\033[1;32mOK\033[0m\n");
	gui_build_font(gui);
}

void		gui_alloc(void)
{
	t_gui	*gui;

	gui = get_gui();
	//if ((gui = (t_gui *)malloc(sizeof(t_gui))) == NULL)
	//	error(1);
	if ((gui->color = (t_color *)malloc(sizeof(t_color))) == NULL)
		error(1);
	if ((gui->display = (SDL_DisplayMode *)malloc(sizeof(SDL_DisplayMode))) == NULL)
		error(1);
	if ((gui->ttf = (t_ttf *)malloc(sizeof(t_ttf))) == NULL)
		error(1);
}

t_gui		*gui_init(void)
{
	t_gui *gui;

	printf("\nGUI : \033[33mINITIALIZING COMPONENT...\033[0m\n");
	printf("GUI : \033[33mSDL_TTF ... \033[0m: ");
	if (TTF_Init() == 0)
		printf("\033[1;32mOK\033[0m\n");
	else
		gui_error(5);
	gui_alloc();
	gui = get_gui();
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
	printf("GUI : \033[1;32mCOMPONENT INITIALIZED\033[0m\n\n");
	gui_build(gui);
	printf("GUI : \033[1;32mCONTENT BUILT\033[0m\n\n");
	printf("GUI : \033[33mApplying Render...\033[0m : ");
	SDL_RenderPresent(gui->img);
	printf("\033[1;32mDISPLAYED\033[0m\n\n");
	SDL_DestroyRenderer(gui->img);
	return (gui);
}
