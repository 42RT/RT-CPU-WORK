#include <gui.h>

void	gui_pixel_put(t_gui *gui, int x, int y)
{
	SDL_SetRenderDrawColor(gui->img, gui->color.r, gui->color.g, gui->color.b, gui->color.a);
	SDL_RenderDrawPoint(gui->img, x, y);
}
