#include <rt.h>

void	gui_button_selected(t_gui *gui, t_button *button)
{
	gui_font_init(gui, "Starjedi", GUI_FONT_SIZE);
	gui_widget_draw_outline(gui, button->dest, 0, "red brick");
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
		i++;
	}
}

void	gui_widget_draw_outline(t_gui *gui, SDL_Rect widget, int outline, char *color)
{
	int i;
	int j;
	
	i = widget.x - outline;
	while (i < widget.w + widget.x + outline)
	{
		j = widget.y - outline;
		while (j < widget.h + widget.y + outline)
		{
			if (i <= widget.x || i >= widget.x + widget.w
			|| j <= widget.y || j >= widget.y + widget.h)
			{
				gui->color = gui_color(color);
				gui_pixel_put(gui, i, j);
			}
			j++;
		}
		i++;
	}
}

void	gui_button_get_bmp(t_gui *gui, int id, int i)
{
	BUTTON[i]->surface = SDL_LoadBMP(GUI_TEXTURE_PATH"button_jade.bmp");
	if (!BUTTON[i]->surface)
		gui_error(2);
	BUTTON[i]->bmp = SDL_CreateTextureFromSurface(gui->img,
		BUTTON[i]->surface);
	if (!BUTTON[i]->bmp)
		gui_error(3);
}

void	gui_button_display(t_gui *gui, int id, int i)
{
	if (BUTTON[i]->align == GUI_ALIGN_LEFT)
		BUTTON[i]->dest.x = 10;
	else if (BUTTON[i]->align == GUI_ALIGN_MID)
		BUTTON[i]->dest.x = (GUI_WIDTH / 2) - (BUTTON[i]->dest.w / 2);
	else if (BUTTON[i]->align == GUI_ALIGN_RIGHT)
		BUTTON[i]->dest.x = GUI_WIDTH - (BUTTON[i]->dest.w + 10);
	else
		BUTTON[i]->dest.x = BUTTON[i]->align;
	BUTTON[i]->dest.y = BLOCK[id]->up_lim + (BLOCK[id]->px / 7);
	SDL_RenderCopy(gui->img, BUTTON[i]->bmp, NULL, &BUTTON[i]->dest);
	SDL_DestroyTexture(BUTTON[i]->bmp);
	SDL_FreeSurface(BUTTON[i]->surface);
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
				gui_button_get_bmp(gui, id, i);
				gui_button_display(gui, id ,i);
				gui_widget_draw_outline(gui, BUTTON[i]->dest, GUI_OUTLINE_PX, "white");
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
