#include <rt.h>

void	gui_help_get_bmp_n_display(t_gui *gui)
{
	HELP->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"help_black.bmp");
	if (!HELP->surface)
		gui_error(2);
	HELP->bmp = SDL_CreateTextureFromSurface(gui->img, HELP->surface);
	if (!HELP->bmp)
		gui_error(3);
	SDL_SetTextureBlendMode(HELP->bmp, SDL_BLENDMODE_BLEND);
	printf("%d\n", SDL_SetTextureAlphaMod(HELP->bmp, 240));
	HELP->dest.x = 20;
	HELP->dest.y = 20;
	HELP->dest.w = GUI_HELP_W;
	HELP->dest.h = GUI_HELP_H;
	SDL_RenderCopy(gui->img, HELP->bmp, NULL, &HELP->dest);
	SDL_DestroyTexture(HELP->bmp);
	SDL_FreeSurface(HELP->surface);
	gui_widget_draw_outline(gui, HELP->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

void	gui_help_open(t_gui *gui)
{
	if ((HELP = (t_help *)malloc(sizeof(t_help))) == NULL)
		error(1);
	if (gui->widget_active)
		event_widget_deselect(gui);
	HELP->nature = "T_HELP";
	gui->widget_active = HELP;
	gui_help_get_bmp_n_display(gui);
}

void	gui_help_close(t_gui *gui)
{
	gui->widget_active = NULL;
	free(HELP);
	HELP = NULL;
	gui_main_refresh(gui);
}

void	gui_help_toggle(t_gui *gui)
{
	if (HELP)
		gui_help_close(gui);
	else
		gui_help_open(gui);
}
