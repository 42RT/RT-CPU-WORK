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

#include <gui.h>
#include <rtdefs.h>
#include <parser.h>

t_gui		*get_gui(void)
{
	static t_gui	gui;

	return (&gui);
}

void		gui_build_main(t_gui *gui)
{
	ft_printf("GUI : \033[33mBUILDING CONTENT ...\033[0m\n");
	gui_background_get_set_n_display(gui);
	ft_printf("GUI : \033[33mContainer \033[0m: ");
	ft_printf("\033[1;32mOK\033[0m\n");
	ft_printf("GUI : \033[33mTextbox \033[0m: ");
	gui_textbox_create_all(gui);
	ft_printf("\033[1;32mOK\033[0m\n");
	ft_printf("GUI : \033[33mButton \033[0m: ");
	gui_button_create_all(gui);
	ft_printf("\033[1;32mOK\033[0m\n");
	ft_printf("GUI : \033[33mScroll \033[0m: ");
	gui_scroll_build(gui);
	ft_printf("\033[1;32mOK\033[0m\n");
	ft_printf("GUI : \033[33mFont \033[0m: ");
	gui_font_build(gui);
	ft_printf("\033[1;32mOK\033[0m\n");
}

void		gui_alloc(void)
{
	t_gui	*gui;

	gui = get_gui();
	if (!(gui->display = (SDL_DisplayMode *)malloc(sizeof(SDL_DisplayMode))))
		error(1);
	if (!(gui->ttf = (t_ttf *)malloc(sizeof(t_ttf))))
		error(1);
	if (!(BG = (t_bg *)malloc(sizeof(t_bg))))
		error(1);
	if (!(PATH = (t_path *)malloc(sizeof(t_path))))
		error(1);
	if (!(DEF = (t_def_widget *)malloc(sizeof(t_def_widget))))
		error(1);
	HELP = NULL;
	PARAM = NULL;
	WIDGET = NULL;
}

t_gui		*gui_init(void)
{
	t_gui	*gui;

	setbuf(stdout, NULL);
	if (TTF_WasInit() || (TTF_Init() == 0))
		ft_printf("\033[1;32mTTF INITIALIZED\033[0m\n");
	else
		gui_error(5);
	gui_alloc();
	gui = get_gui();
	if (SDL_GetCurrentDisplayMode(0, gui->display) != 0)
		gui_error(1);
	gui->display->w = 1920;
	gui->display->h = 1080;
	gui_parse_builder(gui, "./ressources/gui.build");
	gui->win = SDL_CreateWindow("Tool box", gui->dest.x, gui->dest.y,
			gui->dest.w, gui->dest.h, SDL_WINDOW_SHOWN);
	if (gui->win)
		gui->img = SDL_CreateRenderer(gui->win, -1, SDL_RENDERER_SOFTWARE);
	else
		gui_error(4);
	gui->winID = SDL_GetWindowID(gui->win);
	gui->tmp_lim = 0;
	gui_build_main(gui);
	SDL_RenderPresent(gui->img);
	return (gui);
}
