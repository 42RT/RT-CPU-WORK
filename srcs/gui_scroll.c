#include <rt.h>

void	gui_scroll_value_free(char **value, int nb)
{
	int i;

	i = nb - 1;
	while (i >= 0)
		value[i--] = NULL;
}

void	gui_scroll_free(t_scroll *scroll)
{
	gui_button_free(scroll->button);
	scroll->tag = NULL;
	gui_scroll_value_free(scroll->value, scroll->nb_value);
	free(scroll);
}

void	gui_block_scroll_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((SCROLL = (t_scroll **)malloc(sizeof(t_scroll *) * nb)) == NULL)
		error(1);
	BLOCK[id]->scroll_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((SCROLL[i] = (t_scroll *)malloc(sizeof(t_scroll))) == NULL)
			error(1);
		if ((SCROLL_B = (t_button *)malloc(sizeof(t_button))) == NULL)
			error(1);
		if ((SCROLL[i]->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
			error(1);
		if ((SCROLL[i]->value = (char **)malloc(sizeof(char *) * 10)) == NULL)
			error(1);
		SCROLL[i]->value[0] = "valeur 1";
		SCROLL[i]->value[1] = "valeur 2";
		SCROLL[i]->value[2] = "valeur 3";
		SCROLL[i]->value[3] = "valeur 4";
		SCROLL[i]->value[4] = "valeur 5";
		SCROLL[i]->value[5] = "valeur 6";
		SCROLL[i]->value[6] = "valeur 7";
		SCROLL[i]->value[7] = "valeur 8";
		SCROLL[i]->value[8] = "valeur 9";
		SCROLL[i]->value[9] = "valeur 10";
		SCROLL[i]->active_value = 0;
		SCROLL[i]->nb_value = 10;
		SCROLL[i]->mod = 0;
		SCROLL[i]->align = -1;
		SCROLL[i]->nature = SCL;
		SCROLL[i]->surface = NULL;
		SCROLL[i]->bmp = NULL;
		SCROLL_B->surface = NULL;
		SCROLL_B->bmp = NULL;
		SCROLL_B->action = "scroll";
		i++;
	}
}

void	gui_scroll_set_align(t_scroll *scroll)
{
	if (scroll->align == GUI_ALIGN_LEFT)
		scroll->dest.x = 40;
	else if (scroll->align == GUI_ALIGN_MID)
		scroll->dest.x = (GUI_WIDTH / 2) - (scroll->dest.w / 2) + 10;
	else if (scroll->align == GUI_ALIGN_RIGHT)
		scroll->dest.x = GUI_WIDTH - scroll->dest.w - 50;
	else
		scroll->dest.x = scroll->align;
}

void	gui_scroll_set(int id, char *tag, int align_v, int align_h)
{
	t_gui	*gui;
	int		i;

	gui = get_gui();
	i = 0;
	while (i < BLOCK[id]->scroll_qt)
	{
		if (SCROLL[i]->align == -1)
		{
			SCROLL[i]->tag = tag;
			SCROLL[i]->align = align_v;
			SCROLL[i]->p = id;
			SCROLL[i]->id = i;
			SCROLL[i]->dest.w = (GUI_WIDTH / 3) - 20;
			SCROLL[i]->dest.h = GUI_SCROLL_H;
			SCROLL[i]->dest.y = BLOCK[id]->up_lim + align_h;
			gui_scroll_set_align(SCROLL[i]);
			SCROLL_B->dest.y = SCROLL[i]->dest.y;
			SCROLL_B->dest.w = GUI_SCROLL_H;
			SCROLL_B->dest.h = GUI_SCROLL_H;
			SCROLL_B->dest.x = SCROLL[i]->dest.x + SCROLL[i]->dest.w;
			i = BLOCK[id]->scroll_qt;
		}
		i++;
	}
}

void	gui_scroll_value_write(t_gui *gui, t_scroll *scroll, char *color)
{
	gui_font_init(gui, "Starjedi", 16);
	TTF_SizeText(TTF->font, scroll->value[scroll->active_value], &TTF->w_px, &TTF->h_px);
	TTF->texture = SDL_CreateTextureFromSurface(gui->img,
		TTF_RenderText_Solid(TTF->font, scroll->value[scroll->active_value], gui_color(color)));
	SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
	TTF->rect.x = scroll->dest.x + 5;
	TTF->rect.y = scroll->dest.y - 4;
	SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
	gui_anti_aliasing_set(TTF->rect.x, TTF->rect.y, TTF->w_px, TTF->h_px);
	SDL_DestroyTexture(TTF->texture);
	TTF_CloseFont(TTF->font);
}

void	gui_scroll_create_all(t_gui *gui)
{
	int	i;
	int	id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->scroll == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->scroll_qt)
			{
				gui_widget_texture_get_bmp(SCROLL[i], "textbox_white.bmp");
				gui_widget_display(SCROLL[i]);
				gui_widget_draw_in_line(SCROLL[i]->dest, 1, "black");
				gui_scroll_value_write(gui, SCROLL[i], "black");
				SCROLL_B->align = SCROLL[i]->dest.x + SCROLL[i]->dest.w;
				gui_widget_texture_get_bmp(SCROLL_B, "scrollB_jade.bmp");
				gui_widget_display(SCROLL_B);
				gui_widget_draw_in_line(SCROLL_B->dest, 1, "black");
				i++;
			}
			id++;
		}
	}
}

int		gui_scroll_value_select(t_gui *gui, SDL_Event event, t_scroll *scroll)
{
	if ((event.button.x >= scroll->dest.x) &&
	(event.button.x <= scroll->dest.x + scroll->dest.w) &&
	(event.button.y >= scroll->dest.y) &&
	(event.button.y <= scroll->dest.y + scroll->dest.h))
	{
		scroll->active_value = (event.button.y - scroll->dest.y + (scroll->mod * GUI_LIST_STEP)) / GUI_LIST_STEP;
		//printf("scroll select %s\n", scroll->value[scroll->active_value]);
		gui_scroll_toggle(gui, scroll);
		return (1);
	}
	return (0);
}

void	gui_scroll_write_list(t_gui *gui, t_scroll *scroll, int motion)
{
	int	i;

	i = scroll->mod;
	gui_font_init(gui, "Starjedi", 16);
	while (i < scroll->nb_value + scroll->mod && i < GUI_SCROLL_MAX_SHOWN + scroll->mod)
	{
		TTF_SizeText(TTF->font, scroll->value[i], &TTF->w_px, &TTF->h_px);
		if (i == motion)
			TTF->texture = SDL_CreateTextureFromSurface(gui->img,
			TTF_RenderText_Solid(TTF->font, scroll->value[i], gui_color("teal")));
		else
			TTF->texture = SDL_CreateTextureFromSurface(gui->img,
			TTF_RenderText_Solid(TTF->font, scroll->value[i], gui_color("black")));
		SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
		TTF->rect.x = scroll->dest.x + 3;
		TTF->rect.y = (scroll->dest.y - GUI_SCROLL_H - 4) + ((i - scroll->mod + 1) * GUI_LIST_STEP);
		SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
		gui_anti_aliasing_set(TTF->rect.x, TTF->rect.y, TTF->w_px, TTF->h_px);
		SDL_DestroyTexture(TTF->texture);
		i++;
	}
	TTF_CloseFont(TTF->font);
}

void	gui_scroll_open(t_gui *gui, t_scroll *scroll)
{
	if (WIDGET)
		event_widget_deselect(gui);
	WIDGET = scroll;
	//printf("WIDGET ACTIVE = %d\n", *(int *)WIDGET);
	gui_widget_texture_get_bmp(scroll->button, "scrollB_jade_selected.bmp");
	gui_widget_display(scroll->button);
	gui_widget_draw_in_line(scroll->button->dest, 1, "black");
	gui_widget_texture_get_bmp(scroll, "scroll_white.bmp");
	scroll->align = scroll->dest.x;
	scroll->dest.y += GUI_SCROLL_H;
	if (scroll->nb_value < GUI_SCROLL_MAX_SHOWN)
		scroll->dest.h *= scroll->nb_value;
	else
		scroll->dest.h *= GUI_SCROLL_MAX_SHOWN;
	gui_widget_display(scroll);
	gui_scroll_write_list(gui, scroll, -1);
}

void	gui_scroll_close(t_gui *gui, t_scroll *scroll)
{
	WIDGET = NULL;
	//printf("WIDGET NULL\n");
	scroll->dest.y -= GUI_SCROLL_H;
	if (scroll->nb_value < GUI_SCROLL_MAX_SHOWN)
		scroll->dest.h /= scroll->nb_value;
	else
		scroll->dest.h /= GUI_SCROLL_MAX_SHOWN;
	gui_main_refresh(gui);
}

void	gui_scroll_toggle(t_gui *gui, t_scroll *scroll)
{
	if (WIDGET == scroll)
		gui_scroll_close(gui, scroll);
	else
		gui_scroll_open(gui, scroll);
}

void	gui_scroll_build(t_gui *gui)
{
	gui_block_scroll_init(gui, 0, 2);
	gui_block_scroll_init(gui, 6, 1);
	gui_block_scroll_init(gui, 7, 2);
	gui_scroll_set(0, "SCN", GUI_ALIGN_MID, 15);
	gui_scroll_set(0, "OBJ", GUI_ALIGN_MID, 45);
	gui_scroll_set(6, "MTR", GUI_ALIGN_MID, 15);
	gui_scroll_set(7, "PCD", GUI_ALIGN_LEFT, 45);
	gui_scroll_set(7, "NML", GUI_ALIGN_RIGHT, 45);
	gui_scroll_create_all(gui);
}
