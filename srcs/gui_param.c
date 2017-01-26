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

void	gui_param_scroll_init(t_gui *gui, int nb)
{
	int i;

	if ((PARAM->scroll = (t_scroll **)malloc(sizeof(t_scroll *) * nb)) == NULL)
		error(1);
	PARAM->scroll_qt = nb;
	PARAM->active = 0;
	i = 0;
	while (i < nb)
	{
		if ((PARAM_SCL = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
			error(1);
		if ((PARAM_SCL->value = (char **)malloc(sizeof(char *) * 6)) == NULL)
			error(1);
		if ((PARAM_SCL_B = (t_button *)malloc(sizeof(t_button))) == NULL)
			error(1);
		if ((PARAM_SCL->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
			error(1);
		PARAM_SCL->value[0] = "param1";
		PARAM_SCL->value[1] = "param2";
		PARAM_SCL->value[2] = "param3";
		PARAM_SCL->value[3] = "param4";
		PARAM_SCL->value[4] = "param5";
		PARAM_SCL->value[5] = "param6";
		PARAM_SCL->active_value = 0;
		PARAM_SCL->nb_value = 6;
		PARAM_SCL->mod = 0;
		PARAM_SCL->align = -1;
		PARAM_SCL->nature = SCL;
		PARAM_SCL->surface = NULL;
		PARAM_SCL->bmp = NULL;
		PARAM_SCL_B->surface = NULL;
		PARAM_SCL_B->bmp = NULL;
		PARAM_SCL_B->action = "scroll";
		i++;
	}
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
			PARAM_SCL->dest.w = (GUI_WIDTH / 3) - 20;
			PARAM_SCL->dest.h = GUI_SCROLL_H;
			PARAM_SCL->dest.y = align_h;
			PARAM_SCL_B->dest.y = PARAM_SCL->dest.y;
			PARAM_SCL_B->dest.w = GUI_SCROLL_H;
			PARAM_SCL_B->dest.h = GUI_SCROLL_H;
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
		gui_scroll_get_bmp(gui, PARAM_SCL, "textbox_white.bmp");
		gui_scroll_display(gui, PARAM_SCL);
		gui_scroll_value_write(gui, PARAM_SCL, "black");
		PARAM_SCL_B->align = PARAM_SCL->dest.x + PARAM_SCL->dest.w;
		gui_button_get_bmp(gui, PARAM_SCL_B, "scroll_jade.bmp");
		gui_button_display(gui, PARAM_SCL_B);
		gui_widget_draw_in_line(gui, PARAM_SCL_B->dest, 1, "black");
		i++;
	}
}

void	gui_param_build(t_gui *gui)
{
	if (!PARAM->scroll)
		gui_param_scroll_init(gui, 1);
	gui_param_scroll_set(gui, "RES", GUI_ALIGN_LEFT, 45);
	gui_param_scroll_create_all(gui);
	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	gui_write_param(gui, "options", GUI_ALIGN_MID, 20);
	TTF_CloseFont(TTF->font);
}

void	gui_param_open(t_gui *gui)
{
	if (!PARAM)
	{
		if ((PARAM = (t_param *)malloc(sizeof(t_param))) == NULL)
			error(1);
		PARAM->scroll = NULL;
		PARAM->nature = PRM;
	}
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
	gui_font_init(gui, "Audiowide-Regular", GUI_FONT_SIZE + 1);
	gui_write_param(gui, "options", GUI_ALIGN_MID, 20);
	TTF_CloseFont(TTF->font);
}
