#include <rt.h>

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
		if ((SCROLL[i]->value = (char **)malloc(sizeof(char *) * 3)) == NULL)
			error(1);
		SCROLL[i]->value[0] = "valeur 1";
		SCROLL[i]->value[1] = "valeur 2";
		SCROLL[i]->active_value = 0;
		SCROLL[i]->nb_value = 2;
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
			SCROLL_B->dest.y = SCROLL[i]->dest.y;
			SCROLL_B->dest.w = GUI_SCROLL_H;
			SCROLL_B->dest.h = GUI_SCROLL_H;
			i = BLOCK[id]->scroll_qt;
		}
		i++;
	}
}

void	gui_scroll_get_bmp(t_gui *gui, t_scroll *scroll, char *file)
{
	scroll->surface = SDL_LoadBMP(ft_strjoin(GUI_TEXTURE_PATH, file));
	if (!scroll->surface)
		gui_error(2);
	scroll->bmp = SDL_CreateTextureFromSurface(gui->img, scroll->surface);
	if (!scroll->bmp)
		gui_error(3);
}

void	gui_scroll_display(t_gui *gui, t_scroll *scroll)
{
	if (scroll->align == GUI_ALIGN_LEFT)
		scroll->dest.x = 40;
	else if (scroll->align == GUI_ALIGN_MID)
		scroll->dest.x = (GUI_WIDTH / 2) - (scroll->dest.w / 2) + 10;
	else if (scroll->align == GUI_ALIGN_RIGHT)
		scroll->dest.x = GUI_WIDTH - scroll->dest.w - 50;
	else
		scroll->dest.x = scroll->align;
	SDL_RenderCopy(gui->img, scroll->bmp, NULL, &scroll->dest);
	SDL_DestroyTexture(scroll->bmp);
	SDL_FreeSurface(scroll->surface);
	gui_widget_draw_in_line(gui, scroll->dest, 1, "black");
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
				gui_scroll_get_bmp(gui, SCROLL[i], "textbox_white.bmp");
				gui_scroll_display(gui, SCROLL[i]);
				gui_scroll_value_write(gui, SCROLL[i], "black");
				SCROLL_B->align = SCROLL[i]->dest.x + SCROLL[i]->dest.w;
				gui_button_get_bmp(gui, SCROLL_B, "scroll_jade.bmp");
				gui_button_display(gui, SCROLL_B);
				gui_widget_draw_in_line(gui, SCROLL_B->dest, 1, "black");
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
		scroll->active_value = (event.button.y - scroll->dest.y) / GUI_LIST_STEP;
		printf("scroll select %s\n", scroll->value[scroll->active_value]);
		gui_scroll_toggle(gui, scroll);
		return (1);
	}
	return (0);
}

void	gui_scroll_write_list(t_gui *gui, t_scroll *scroll)
{
	int	i;

	i = 0;
	gui_font_init(gui, "Starjedi", 16);
	while (i < scroll->nb_value)
	{
		TTF_SizeText(TTF->font, scroll->value[i], &TTF->w_px, &TTF->h_px);
		TTF->texture = SDL_CreateTextureFromSurface(gui->img,
			TTF_RenderText_Solid(TTF->font, scroll->value[i], gui_color("black")));
		SDL_QueryTexture(TTF->texture, NULL, NULL, &TTF->rect.w, &TTF->rect.h);
		TTF->rect.x = scroll->dest.x + 3;
		TTF->rect.y = (scroll->dest.y - GUI_SCROLL_H) + ((i + 1) * GUI_LIST_STEP);
		SDL_RenderCopy(gui->img, TTF->texture, NULL, &TTF->rect);
		SDL_DestroyTexture(TTF->texture);
		i++;
	}
	TTF_CloseFont(TTF->font);
}

void	gui_scroll_open(t_gui *gui, t_scroll *scroll)
{
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = scroll;
	gui_button_get_bmp(gui, scroll->button, "scroll_jade_selected.bmp");
	gui_button_display(gui, scroll->button);
	gui_widget_draw_in_line(gui, scroll->button->dest, 1, "black");
	gui_scroll_get_bmp(gui, scroll, "scroll_white.bmp");
	scroll->align = scroll->dest.x;
	scroll->dest.y += GUI_SCROLL_H;
	scroll->dest.h *= scroll->nb_value;
	gui_scroll_display(gui, scroll);
	gui_scroll_write_list(gui, scroll);
}

void	gui_scroll_close(t_gui *gui, t_scroll *scroll)
{
	gui->widget_active = NULL;
	scroll->dest.y -= GUI_SCROLL_H;
	scroll->dest.h /= scroll->nb_value;
	gui_main_refresh(gui);
}

void	gui_scroll_toggle(t_gui *gui, t_scroll *scroll)
{
	if (gui->widget_active == scroll)
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
