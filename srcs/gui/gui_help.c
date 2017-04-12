#include <gui.h>

void	gui_help_build(t_gui *gui)
{
	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	gui_write_help(gui, "shortcut", GUI_ALIGN_MID, 20);
	gui_write_help(gui, "[text event]", GUI_ALIGN_LEFT, 45);
	gui_write_help(gui, "(key)", GUI_ALIGN_RIGHT, 45);
	gui_write_help(gui, "       -----------------------", GUI_ALIGN_LEFT, 60);
	gui_write_help(gui, "[set pos/neg]", GUI_ALIGN_LEFT, 75);
	gui_write_help(gui, "(pavnum +/-)", GUI_ALIGN_RIGHT, 75);
	gui_write_help(gui, "[del last num]", GUI_ALIGN_LEFT, 95);
	gui_write_help(gui, "(backspace)", GUI_ALIGN_RIGHT, 95);
	gui_write_help(gui, "[del entry]", GUI_ALIGN_LEFT, 115);
	gui_write_help(gui, "(delete)", GUI_ALIGN_RIGHT, 115);
	gui_write_help(gui, "[next entry]", GUI_ALIGN_LEFT, 135);
	gui_write_help(gui, "(tab)", GUI_ALIGN_RIGHT, 135);
	gui_write_help(gui, "[validate entry]", GUI_ALIGN_LEFT, 155);
	gui_write_help(gui, "(enter/return)", GUI_ALIGN_RIGHT, 155);
	TTF_CloseFont(TTF->font);
}

void	gui_help_get_bmp_n_display(t_gui *gui)
{
	gui_widget_texture_get_bmp(HELP, "help_black.bmp");
	SDL_SetTextureBlendMode(HELP->bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(HELP->bmp, 240);
	gui_widget_display(HELP);
	gui_widget_draw_outline(HELP->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

void	gui_help_open(t_gui *gui)
{
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = HELP;
	HELP->active = 1;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_button_selected(gui, BLOCK[9]->button[1]);
	gui_help_get_bmp_n_display(gui);
	gui_help_build(gui);
}

void	gui_help_close(t_gui *gui)
{
	gui->widget_active = NULL;
	HELP->active = 0;
	printf("WIDGET NULL\n");
	gui_main_refresh(gui);
}

void	gui_help_toggle(t_gui *gui)
{
	if (HELP->active == 1)
		gui_help_close(gui);
	else
		gui_help_open(gui);
}
