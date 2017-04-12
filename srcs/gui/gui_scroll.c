#include <gui.h>

void	gui_scroll_value_free(char **value, int nb)
{
	int i;

	i = nb - 1;
	while (i >= 0)
		value[i--] = NULL;
}

void	gui_reparse_scroll_value(t_gui *gui, char *target)
{
	int	i;
	int	id;

	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
	{
		id = 2;
		while (id < GUI_CONTAINER_TOTAL_NB)
		{
			if (BLOCK[id]->scroll == NULL)
				id++;
			else
			{
				i = 0;
				while (i < BLOCK[id]->scroll_qt)
				{
					free(SCROLL[i]->value);
					SCROLL[i]->value = gui_get_scroll_value(SCROLL[i]);
					i++;
				}
				id++;
			}
		}
	}
	else if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 1;
		while (i < PARAM->scroll_qt)
		{
			free(PARAM_SCL->value);
			PARAM_SCL->value = gui_get_scroll_value(PARAM_SCL);
			i++;
		}
	}
}

void	gui_scroll_set_halign(t_scroll *scroll)
{
	t_gui	*gui;

	gui = get_gui();
	if (scroll->dest.x == GUI_ALIGN_LEFT)
		scroll->dest.x = GUI_FONT_BORDER_STEP + 35;
	else if (scroll->dest.x == GUI_ALIGN_MID)
		scroll->dest.x = (GUI_WIDTH / 2) - (scroll->dest.w / 2) + 10;
	else if (scroll->dest.x == GUI_ALIGN_RIGHT)
		scroll->dest.x = GUI_WIDTH - scroll->dest.w - 50;
	else
		scroll->dest.x = scroll->dest.x;
}

void	gui_scroll_set(t_scroll *scroll)
{
	t_gui	*gui;

	gui = get_gui();
	scroll->dest.w = DEF->scl_w;
	scroll->dest.h = DEF->scl_h;
	scroll->dest.y += BLOCK[scroll->p]->dest.y;
	gui_scroll_set_halign(scroll);
	scroll->button->dest.x = scroll->dest.x + scroll->dest.w;
	scroll->button->dest.y = scroll->dest.y;
	scroll->button->dest.w = DEF->scl_h;
	scroll->button->dest.h = DEF->scl_h;
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
	t_env *e;
	char	*scene;

	e = get_env();
	if ((event.button.x >= scroll->dest.x) &&
	(event.button.x <= scroll->dest.x + scroll->dest.w) &&
	(event.button.y >= scroll->dest.y) &&
	(event.button.y <= scroll->dest.y + scroll->dest.h))
	{
		scroll->active_value = (event.button.y - scroll->dest.y + (scroll->mod * GUI_LIST_STEP)) / GUI_LIST_STEP;
		//printf("scroll select %s\n", scroll->value[scroll->active_value]);
		scene = ft_strjoin("scene/", scroll->value[scroll->active_value]);
		scene = ft_strjoin(scene, ".rts");
		if (!ft_strcmp(scroll->tag, "SCN") && (ft_strcmp(scene, e->av[1])))
			gui_rt_reload(e, gui, scene);
		else
		{
			if (!ft_strcmp(scroll->tag, "OBJ"))
			{
				gui_reparse_textbox_value(gui, "ALL");
				gui_reparse_scroll_value(gui, "ALL");
			}
			gui_scroll_toggle(gui, scroll);
		}
		free(scene);
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
	gui_scroll_create_all(gui);
}
