#include <gui.h>

int		gui_rgba_constraint(int i)
{
	if (i > 255)
	{
		//printf("too high : %d\n", i);
		i = 255;
	}
	if (i < 0)
	{
		//printf("too low : %d\n", i);
		i = 0;
	}
	return (i);
}

void	gui_add_pixel(int x, int y, int coef)
{
	unsigned int	pixel;
	t_gui			*gui;
	SDL_Rect		target;

	target.w = 1;
	target.h = 1;
	target.x = x;
	target.y = y;
	gui = get_gui();
	if (SDL_RenderReadPixels(gui->img, &target, SDL_PIXELFORMAT_ARGB8888, &pixel, GUI_WIDTH * 32) < 0)
		gui_error(7);
	gui->p_color.r += ((pixel & 0xFF0000)>>16) / (5 - coef);
	gui->p_color.r = gui_rgba_constraint(gui->p_color.r);
	gui->p_color.g += ((pixel & 0x00FF00)>>8) / (5 - coef);
	gui->p_color.g = gui_rgba_constraint(gui->p_color.g);
	gui->p_color.b += (pixel & 0x0000FF) / (5 - coef);
	gui->p_color.b = gui_rgba_constraint(gui->p_color.b);
	if (((((pixel & 0xFF0000)>>16 == 255) && ((pixel & 0x00FF00)>>8 == 255)
	&& ((pixel & 0x0000FF) == 255)))
	|| ((((pixel & 0xFF0000)>>16 == 0) && ((pixel & 0x00FF00)>>8 == 0))
	&& ((pixel & 0x0000FF) == 0)))
		return;
}

int		gui_check_pixel(int x, int y, int coef)
{
	unsigned int	pixel;
	t_gui			*gui;
	SDL_Rect		target;

	target.w = 1;
	target.h = 1;
	target.x = x;
	target.y = y;
	gui = get_gui();
	if (SDL_RenderReadPixels(gui->img, &target, SDL_PIXELFORMAT_ARGB8888, &pixel, GUI_WIDTH * 32) < 0)
		gui_error(7);
	//printf("PIXEL[%d][%d] = {%d,%d,%d}\n", x, y, (pixel & 0xFF0000)>>16, (pixel & 0x00FF00)>>8, (pixel & 0x0000FF));
	gui->p_color.r += ((pixel & 0xFF0000)>>16) / (5 - coef);
	gui->p_color.r = gui_rgba_constraint(gui->p_color.r);
	gui->p_color.g += ((pixel & 0x00FF00)>>8) / (5 - coef);
	gui->p_color.g = gui_rgba_constraint(gui->p_color.g);
	gui->p_color.b += (pixel & 0x0000FF) / (5 - coef);
	gui->p_color.b = gui_rgba_constraint(gui->p_color.b);
	if (((pixel & 0xFF0000)>>16 == 255) && ((pixel & 0x00FF00)>>8 == 255) 
	&& ((pixel & 0x0000FF) == 255))
		return (1);
	//if (((pixel & 0xFF0000)>>16 == 0) && ((pixel & 0x00FF00)>>8 == 0) 
	//&& ((pixel & 0x0000FF) == 0))
	//	return (1);
	return (-1);
}

void	gui_draw_anti_aliased_pixel(t_gui *gui, int x, int y)
{
	SDL_SetRenderDrawColor(gui->img, gui->p_color.r, gui->p_color.g, gui->p_color.b, 255);
	SDL_RenderDrawPoint(gui->img, x, y);
}

int		gui_get_adjacent_color_filter(t_gui *gui, SDL_Rect target)
{
	gui->p_color.r = 0;
	gui->p_color.g = 0;
	gui->p_color.b = 0;
	if (gui_check_pixel(target.x, target.y, 0) == 1)
	{
		if (target.x + 1 < GUI_WIDTH)
			gui_add_pixel(target.x + 1, target.y, 0);
		if (target.x - 1 >= 0)
			gui_add_pixel(target.x - 1, target.y, 0);
		if (target.y + 1 < GUI_HEIGHT)
			gui_add_pixel(target.x, target.y + 1, 0);
		if (target.y - 1 >= 0)
			gui_add_pixel(target.x, target.y - 1, 0);
		return (1);
	}
	return (-1);
}

void		gui_anti_aliasing(t_gui *gui, SDL_Rect zone)
{
	int			i;
	int			j;
	SDL_Rect	target;

	target.w = 1;
	target.h = 1;
	i = 0;
	while (i < zone.w)
	{
		j = 0;
		while (j < zone.h)
		{
			target.x = i + zone.x;
			target.y = j + zone.y;
			if (gui_get_adjacent_color_filter(gui, target) == 1)
				gui_draw_anti_aliased_pixel(gui, target.x, target.y);
			j++;
		}
		i++;
	}
}

void		gui_anti_aliasing_set(int x, int y, int w, int h)
{
	t_gui		*gui;
	SDL_Rect	zone;

	zone.x = x;
	zone.y = y + 5;
	zone.w = w;
	zone.h = h - 10;
	gui = get_gui();
	if (GUI_AA == 1)
		gui_anti_aliasing(gui, zone);
}
