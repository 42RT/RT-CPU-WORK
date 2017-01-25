#include <rt.h>

void	gui_param_build(t_gui *gui)
{
	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	gui_write_param(gui, "options", GUI_ALIGN_MID, 20);
	TTF_CloseFont(TTF->font);
}

void	gui_param_get_bmp_n_display(t_gui *gui)
{
	PARAM->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"help_black.bmp");
	if (!PARAM->surface)
		gui_error(2);
	PARAM->bmp = SDL_CreateTextureFromSurface(gui->img, PARAM->surface);
	if (!PARAM->bmp)
		gui_error(3);
	SDL_SetTextureBlendMode(PARAM->bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(PARAM->bmp, 240);
	PARAM->dest.x = 20;
	PARAM->dest.y = 20;
	PARAM->dest.w = GUI_HELP_W;
	PARAM->dest.h = GUI_HELP_H;
	SDL_RenderCopy(gui->img, PARAM->bmp, NULL, &PARAM->dest);
	SDL_DestroyTexture(PARAM->bmp);
	SDL_FreeSurface(PARAM->surface);
	gui_widget_draw_outline(gui, PARAM->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

void	gui_param_open(t_gui *gui)
{
	if ((PARAM = (t_param *)malloc(sizeof(t_param))) == NULL)
		error(1);
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = PARAM;
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_build(gui);
}

void	gui_param_close(t_gui *gui)
{
	gui->widget_active = NULL;
	free(PARAM);
	PARAM = NULL;
	gui_main_refresh(gui);
}

void	gui_param_toggle(t_gui *gui)
{
	if (PARAM)
		gui_param_close(gui);
	else
		gui_param_open(gui);
}
