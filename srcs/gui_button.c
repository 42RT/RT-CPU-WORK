#include <rt.h>

void	gui_button_selected(t_gui *gui, t_button *button)
{
	gui_font_init(gui, "Starjedi", GUI_FONT_SIZE);
	gui_widget_draw_depth(gui, button->dest, GUI_BUTTON_DEPTH, "red brick");
	gui_write_button(button->action, button, "red brick");
	TTF_CloseFont(TTF->font);
}

void	gui_block_button_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((BUTTON = (t_button **)malloc(sizeof(t_button *) * nb)) == NULL)
		error(1);
	BLOCK[id]->button_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((BUTTON[i] = (t_button *)malloc(sizeof(t_button))) == NULL)
			error(1);
		BUTTON[i]->align = -1;
		BUTTON[i]->surface = NULL;
		BUTTON[i]->bmp = NULL;
		BUTTON[i]->dest.y = BLOCK[id]->up_lim + (BLOCK[id]->px / 7);
		i++;
	}
}

void	gui_widget_draw_depth(t_gui *gui, SDL_Rect widget, int px, char *color)
{
	int i;
	int j;
	
	i = widget.x - px;
	while (i < widget.w + widget.x)
	{
		j = widget.y - px;
		while (j < widget.h + widget.y)
		{
			if (i < widget.x || j < widget.y)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_widget_draw_outline(t_gui *gui, SDL_Rect widget, int px, char *color)
{
	int i;
	int j;
	
	i = widget.x - px;
	while (i < widget.w + widget.x + px)
	{
		j = widget.y - px;
		while (j < widget.h + widget.y + px)
		{
			if (i < widget.x || i >= widget.x + widget.w
			|| j < widget.y || j >= widget.y + widget.h)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_widget_draw_in_line(t_gui *gui, SDL_Rect widget, int px, char *color)
{
	int i;
	int j;
	
	i = widget.x;
	while (i < widget.w + widget.x)
	{
		j = widget.y;
		while (j < widget.h + widget.y)
		{
			if (i < widget.x + px || i >= widget.x + widget.w - px
			|| j < widget.y + px || j >= widget.y + widget.h - px)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}


void	gui_button_get_bmp(t_gui *gui, t_button *button, char *file)
{
	button->surface = SDL_LoadBMP(ft_strjoin(GUI_TEXTURE_PATH, file));
	if (!button->surface)
		gui_error(2);
	button->bmp = SDL_CreateTextureFromSurface(gui->img,
		button->surface);
	if (!button->bmp)
		gui_error(3);
}

void	gui_button_display(t_gui *gui, t_button *button)
{
	if (button->align == GUI_ALIGN_LEFT)
		button->dest.x = 10;
	else if (button->align == GUI_ALIGN_MID)
		button->dest.x = (GUI_WIDTH / 2) - (button->dest.w / 2);
	else if (button->align == GUI_ALIGN_RIGHT)
		button->dest.x = GUI_WIDTH - (button->dest.w + 10);
	else
		button->dest.x = button->align;
	SDL_RenderCopy(gui->img, button->bmp, NULL, &button->dest);
	SDL_DestroyTexture(button->bmp);
	SDL_FreeSurface(button->surface);
}

void	gui_button_create_all(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->button == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->button_qt)
			{
				gui_button_get_bmp(gui, BUTTON[i], "button_jade.bmp");
				gui_button_display(gui, BUTTON[i]);
				gui_widget_draw_depth(gui, BUTTON[i]->dest, GUI_BUTTON_DEPTH, "white");
				i++;
			}
			id++;
		}
	}
}

void	gui_button_set(int id, char *action, int align, int w, int h)
{
	t_gui	*gui;
	int		i;

	gui = get_gui();
	i = 0;
	while (i < BLOCK[id]->button_qt)
	{
		if (BUTTON[i]->align == -1)
		{
			BUTTON[i]->align = align;
			BUTTON[i]->dest.w = w;
			BUTTON[i]->dest.h = h;
			BUTTON[i]->action = action;
			i = BLOCK[id]->button_qt;
		}
		i++;
	}
}

void	gui_button_build(t_gui *gui)
{
	int w;
	int h;

	gui_block_button_init(gui, 8, 3);
	gui_block_button_init(gui, 9, 3);
	h = 25;//GUI_BUTTON_H;
	w = (GUI_WIDTH - (GUI_FONT_BORDER_STEP * 4)) / 3;
	gui_button_set(8, "del", GUI_ALIGN_LEFT, w, h);
	gui_button_set(8, "save", GUI_ALIGN_MID, w, h);
	gui_button_set(8, "apply", GUI_ALIGN_RIGHT, w, h);
	gui_button_set(9, "param", GUI_ALIGN_LEFT, w, h);
	gui_button_set(9, "help", GUI_ALIGN_MID, w, h);
	gui_button_set(9, "exit", GUI_ALIGN_RIGHT, w, h);
	gui_button_create_all(gui);
}
