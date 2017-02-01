#include <rt.h>

void	gui_param_free(t_param *param)
{
	int i;

	i = 0;
	while (i < param->scroll_qt)
	{
		gui_scroll_free(param->scroll[i]);
		i++;
	}
	free(param);
}

void	gui_param_get_bmp_n_display(t_gui *gui)
{
	gui_widget_texture_get_bmp(PARAM, "help_black.bmp");
	SDL_SetTextureBlendMode(PARAM->bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(PARAM->bmp, 240);
	gui_widget_display(PARAM);
	gui_widget_draw_outline(PARAM->dest, 5, "purple deep");
	SDL_RenderPresent(gui->img);
}

t_scroll	*gui_param_scroll_init(t_gui *gui)
{
	t_scroll	*scroll;

	if ((scroll = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
		error(1);
	scroll->nb_value = 6;
	if ((scroll->value = (char **)malloc(sizeof(char *) * scroll->nb_value))
	== NULL)
		error(1);
	if ((scroll->button = (t_button *)malloc(sizeof(t_button))) == NULL)
		error(1);
	if ((scroll->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
		error(1);
	scroll->value[0] = "param1";
	scroll->value[1] = "param2";
	scroll->value[2] = "param3";
	scroll->value[3] = "param4";
	scroll->value[4] = "param5";
	scroll->value[5] = "param6";
	scroll->active_value = 0;
	scroll->mod = 0;
	scroll->align = -1;
	scroll->nature = SCL;
	scroll->surface = NULL;
	scroll->bmp = NULL;
	scroll->button->surface = NULL;
	scroll->button->bmp = NULL;
	scroll->button->action = "scroll";
	return (scroll);
}

void	gui_param_scroll_set(t_gui *gui, char *tag, int align_v, int align_h)
{
	int i;

	i = 0;
	while (i < PARAM->scroll_qt)
	{
		if (PARAM_SCL->align == -1)
		{
			PARAM_SCL->tag = tag;
			PARAM_SCL->align = align_v;
			PARAM_SCL->p = 0;
			PARAM_SCL->id = i;
			PARAM_SCL->dest.w = (GUI_WIDTH / 3);
			PARAM_SCL->dest.h = GUI_SCROLL_H;
			PARAM_SCL->dest.y = align_h;
			gui_scroll_set_align(PARAM_SCL);
			PARAM_SCL_B->dest.y = PARAM_SCL->dest.y;
			PARAM_SCL_B->dest.w = GUI_SCROLL_H;
			PARAM_SCL_B->dest.h = GUI_SCROLL_H;
			PARAM_SCL_B->dest.x = PARAM_SCL->dest.x + PARAM_SCL->dest.w;
			i = PARAM->scroll_qt;
		}
		i++;
	}
}

void	gui_param_scroll_create_all(t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->scroll_qt)
	{
		gui_widget_texture_get_bmp(PARAM_SCL, "textbox_white.bmp");
		gui_widget_display(PARAM_SCL);
		gui_widget_draw_in_line(PARAM_SCL->dest, 1, "black");
		gui_scroll_value_write(gui, PARAM_SCL, "black");
		PARAM_SCL_B->align = PARAM_SCL->dest.x + PARAM_SCL->dest.w;
		gui_widget_texture_get_bmp(PARAM_SCL_B, "scrollB_jade.bmp");
		gui_widget_display(PARAM_SCL_B);
		gui_widget_draw_in_line(PARAM_SCL_B->dest, 1, "black");
		i++;
	}
}

void	gui_param_text_build(t_gui *gui)
{
	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	gui_write_param(gui, "options", GUI_ALIGN_MID, 20);
	gui_write_param(gui, "Resolution", GUI_ALIGN_LEFT, 45);
	gui_write_param(gui, "Anti-aliasing", GUI_ALIGN_LEFT, 70);
	TTF_CloseFont(TTF->font);

}

void	gui_param_build(t_gui *gui)
{
	if (!PARAM->checkbox)
		gui_param_checkbox_init(gui, 1);
	gui_param_scroll_set(gui, "RES", GUI_ALIGN_RIGHT, 45);
	gui_param_checkbox_set(gui, "_AA", GUI_ALIGN_MID, 70);
	gui_param_scroll_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_text_build(gui);
	}

void	gui_param_open(t_gui *gui)
{
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = PARAM;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_build(gui);
	PARAM->active = 1;
}

void	gui_param_close(t_gui *gui)
{
	gui->widget_active = NULL;
	//printf("WIDGET NULL\n");
	PARAM->active = 0;
	gui_main_refresh(gui);
}

void	gui_param_toggle(t_gui *gui)
{
	if (PARAM && PARAM->active)
		gui_param_close(gui);
	else
		gui_param_open(gui);
}

void	gui_param_refresh(t_gui *gui)
{
	gui->widget_active = PARAM;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_scroll_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_text_build(gui);
}
