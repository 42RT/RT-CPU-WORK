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

void		gui_main_refresh(t_gui *gui)
{
	gui_background_get_set_n_display(gui);
	gui_textbox_create_all(gui);
	gui_button_create_all(gui);
	gui_scroll_create_all(gui);
	gui_font_build(gui);
}

void		gui_build(t_gui	*gui)
{
	printf("GUI : \033[33mBUILDING CONTENT ...\033[0m\n");
	gui_background_get_set_n_display(gui);
	gui->cbcnt = 0;
	gui->container = (t_container **)malloc(sizeof(t_container *)
			* GUI_CONTAINER_TOTAL_NB);
	printf("GUI : \033[33mContainer \033[0m: ");
	/* compter 40 px par ligne dans le conteneur*/
	gui_container_build(gui, GUI_CONSTANT, 80);
	gui_container_build(gui, GUI_CONSTANT, 80);
	gui_container_build(gui, GUI_CONSTANT, 80);
	gui_container_build(gui, GUI_CONSTANT, 120);
	gui_container_build(gui, GUI_CONSTANT, 40);
	gui_container_build(gui, GUI_CONSTANT, 40);
	gui_container_build(gui, GUI_CONSTANT, 40);
	gui_container_build(gui, GUI_CONSTANT, 80);
	gui_container_build(gui, GUI_CONSTANT, 40);
	gui_container_build(gui, GUI_CONSTANT, 40);
	printf("\033[1;32mOK\033[0m\n");
	printf("GUI : \033[33mTextbox \033[0m: ");
	gui_textbox_build(gui);
	printf("\033[1;32mOK\033[0m\n");
	printf("GUI : \033[33mButton \033[0m: ");
	gui_button_build(gui);
	printf("\033[1;32mOK\033[0m\n");
	printf("GUI : \033[33mScroll \033[0m: ");
	gui_scroll_build(gui);
	printf("\033[1;32mOK\033[0m\n");
	printf("GUI : \033[33mFont \033[0m: ");
	gui_font_build(gui);
	printf("\033[1;32mOK\033[0m\n");
}

void		gui_alloc(void)
{
	t_gui	*gui;

	gui = get_gui();
	if ((gui->display = (SDL_DisplayMode *)malloc(sizeof(SDL_DisplayMode))) == NULL)
		error(1);
	if ((gui->ttf = (t_ttf *)malloc(sizeof(t_ttf))) == NULL)
		error(1);
	HELP = NULL;
	PARAM = NULL;
}

t_gui		*gui_init(void)
{
	t_gui *gui;

	setbuf(stdout, NULL);
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
	gui->width = GUI_WIDTH;
	gui->height = GUI_HEIGHT;
	gui->anchor_x = ALT_SCREEN_CENTERED + 800;//(gui->display->w + DEF_IMG_WIDTH) / 2;
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
	printf("GUI : \033[1;32mCONTENT BUILT\033[0m\n");
	printf("GUI : \033[33mApplying Render...\033[0m : ");
	SDL_RenderPresent(gui->img);
	printf("\033[1;32mDISPLAYED\033[0m\n\n");
	return (gui);
}
