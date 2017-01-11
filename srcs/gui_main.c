/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/11 17:49:52 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <rt.h>
# include <rtdefs.h>

void		gui_build(t_gui	*gui)
{
	gui->color->r = 255;
	gui->color->g = 255;
	gui->color->b = 255;
	gui->color->a = 255;
	int i = 0;
	int j = 0;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			pixel_put_gui(gui, i, j);
			j++;
		}
		i++;
		
	}
	SDL_RenderPresent(gui->img);
}

t_gui		*gui_alloc()
{
	t_gui	*gui;

	if ((gui = (t_gui *)malloc(sizeof(t_gui))) == NULL)
		error(1);
	if ((gui->display = (SDL_DisplayMode*)malloc(sizeof(SDL_DisplayMode))) == NULL)
		error(1);
	if ((gui->color = (t_color *)malloc(sizeof(t_color))) == NULL)
		error(1);
	return (gui);
}

t_gui		*gui_init()
{
	t_gui			*gui;

	gui = gui_alloc();
	if (SDL_GetCurrentDisplayMode(0, gui->display) != 0)
		error(9);
	gui->width = DEF_GUI_WIDTH;
	gui->height = DEF_IMG_HEIGHT;
	gui->anchor_x = (gui->display->w + DEF_IMG_WIDTH) / 2;
	gui->anchor_y = SDL_WINDOWPOS_CENTERED;
	gui->win = SDL_CreateWindow("Tool box", gui->anchor_x, gui->anchor_y, gui->width, gui->height, SDL_WINDOW_SHOWN);
	if (gui->win)
		gui->img = SDL_CreateRenderer(gui->win, -1, SDL_RENDERER_SOFTWARE);
	else
		error(8);
	gui_build(gui);
	return (gui);
}
