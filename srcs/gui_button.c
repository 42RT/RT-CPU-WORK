#include <rt.h>

void	gui_button_selected(t_gui *gui, t_button *button)
{
	gui_font_init(gui, "Starjedi", GUI_FONT_SIZE);
	gui_widget_draw_depth(button->dest, GUI_BUTTON_DEPTH, "red brick");
	gui_write_button(button->action, button, "red brick");
	TTF_CloseFont(TTF->font);
}

void	gui_button_free(t_button *button)
{
	button->action = NULL;
	free(button);
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
				gui_widget_texture_get_bmp(BUTTON[i], "button_jade.bmp");
				gui_widget_display(BUTTON[i]);
				gui_widget_draw_depth(BUTTON[i]->dest, GUI_BUTTON_DEPTH, "white");
				i++;
			}
			id++;
		}
	}
}

void	gui_button_set_align(t_button *button)
{
	if (button->align == GUI_ALIGN_LEFT)
		button->dest.x = 10;
	else if (button->align == GUI_ALIGN_MID)
		button->dest.x = (GUI_WIDTH / 2) - (button->dest.w / 2);
	else if (button->align == GUI_ALIGN_RIGHT)
		button->dest.x = GUI_WIDTH - (button->dest.w + 10);
	else
		button->dest.x = button->align;
}

void	gui_button_set(int id, char *action, int align)
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
			BUTTON[i]->dest.w = (GUI_WIDTH - (GUI_FONT_BORDER_STEP * 4)) / 3;
			BUTTON[i]->dest.h = GUI_BUTTON_H;
			gui_button_set_align(BUTTON[i]);
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
	gui_button_set(8, "del", GUI_ALIGN_LEFT);
	gui_button_set(8, "save", GUI_ALIGN_MID);
	gui_button_set(8, "apply", GUI_ALIGN_RIGHT);
	gui_button_set(9, "param", GUI_ALIGN_LEFT);
	gui_button_set(9, "help", GUI_ALIGN_MID);
	gui_button_set(9, "exit", GUI_ALIGN_RIGHT);
	gui_button_create_all(gui);
}
