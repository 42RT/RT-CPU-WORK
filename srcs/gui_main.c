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

# include <gui.h>
# include <rtdefs.h>
# include <parser.h>

t_gui		*get_gui(void)
{
	static	t_gui gui;

	return (&gui);
}

void		gui_rt_reload_object(t_env *e, t_gui *gui)
{
	if ((e->set->oldw != e->set->width) || (e->set->oldh != e->set->width))
		rebuild_rt_window(e);
	if (e->set->verbose)
		print_debug(e);
	if (!libxmlx_reload(e->gfx, e->set->width, e->set->height, BUFF_NB))
		exit(1);
	loading_bar(e, 0, int_to_tcolor(0x0101A0), int_to_tcolor(0));
	if (e->set->preview)
		ft_aff_quick(e, e->obj);
	ft_aff(e, e->obj);
	SDL_RaiseWindow(e->gfx->win);
	gui_scroll_load_object(gui);
	gui_textbox_load_object(gui);
	gui_main_refresh(gui);
}

void		gui_rt_reload(t_env *e, t_gui *gui, char *scene)
{
	e->av[1] = ft_strdup(scene);
	reload(e);
	SDL_RaiseWindow(e->gfx->win);
	gui_scroll_load_object(gui);
	gui_textbox_load_object(gui);
	gui_main_refresh(gui);
}

void		gui_main_refresh(t_gui *gui)
{
	//printf("Refreshing ...");
	gui_background_get_set_n_display(gui);
	gui_textbox_create_all(gui);
	gui_button_create_all(gui);
	gui_scroll_create_all(gui);
	gui_font_build(gui);
	if (PARAM && PARAM->active)
		gui_param_refresh(gui);
	//printf("Done\n");
	gui->action = 0;
}

void		gui_build(t_gui	*gui)
{
	printf("GUI : \033[33mBUILDING CONTENT ...\033[0m\n");
	gui_background_get_set_n_display(gui);
	printf("GUI : \033[33mContainer \033[0m: ");
	/* compter 40 px par ligne dans le conteneur*/
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
	if ((BG = (t_bg *)malloc(sizeof(t_bg))) == NULL)
		error(1);
	if ((PATH = (t_path *)malloc(sizeof(t_path))) == NULL)
		error(1);
	if ((DEF = (t_def_widget *)malloc(sizeof(t_def_widget))) == NULL)
		error(1);
	HELP = NULL;
	PARAM = NULL;
	WIDGET = NULL;
}

t_gui		*gui_init(void)
{
	t_gui *gui;

	setbuf(stdout, NULL);
	printf("\nGUI : \033[33mINITIALIZING COMPONENT...\033[0m\n");
	printf("GUI : \033[33mSDL_TTF ... \033[0m: ");
	if (TTF_WasInit() || (TTF_Init() == 0))
		printf("\033[1;32mOK\033[0m\n");
	else
		gui_error(5);
	gui_alloc();
	gui = get_gui();
	if (SDL_GetCurrentDisplayMode(0, gui->display) != 0)
		gui_error(1);
	gui->display->w = 1920;
	gui->display->h = 1080;
	gui_parse_builder(gui, "./ressources/gui.build");
	//gui->dest.w = GUI_WIDTH;
	//gui->dest.h = GUI_HEIGHT;
	//gui->dest.x = ALT_SCREEN_CENTERED + 800;//(gui->display->w + DEF_IMG_WIDTH) / 2;
	//gui->dest.y = SDL_WINDOWPOS_CENTERED;
	gui->win = SDL_CreateWindow("Tool box", gui->dest.x, gui->dest.y,
			gui->dest.w, gui->dest.h, SDL_WINDOW_SHOWN);
	if (gui->win)
		gui->img = SDL_CreateRenderer(gui->win, -1, SDL_RENDERER_SOFTWARE);
	else
		gui_error(4);
	gui->winID = SDL_GetWindowID(gui->win);
	gui->tmp_lim = 0;
	printf("GUI : \033[1;32mCOMPONENT INITIALIZED\033[0m\n\n");
	gui_build(gui);
	printf("GUI : \033[1;32mCONTENT BUILT\033[0m\n");
	printf("GUI : \033[33mApplying Render...\033[0m : ");
	//gui_anti_aliasing_set(0, 0, GUI_WIDTH, GUI_HEIGHT);
	SDL_RenderPresent(gui->img);
	printf("\033[1;32mDISPLAYED\033[0m\n\n");
	return (gui);
}
