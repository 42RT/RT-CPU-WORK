#include <gui.h>

void	gui_reparse_textbox_value(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				free(TEXTBOX[i]->value);
				gui_get_textbox_value(TEXTBOX[i]);
				i++;
			}
			id++;
		}
	}
}

void	gui_textbox_load_object(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				free(TEXTBOX[i]->value);
				gui_get_textbox_value(TEXTBOX[i]);
				i++;
			}
			id++;
		}
	}
}

void	gui_block_textbox_init(t_gui *gui, int id, int nb)
{
	int i;

	if ((TEXTBOX = (t_textbox **)malloc(sizeof(t_textbox *) * nb)) == NULL)
		error(1);
	BLOCK[id]->textbox_qt = nb;
	i = 0;
	while (i < nb)
	{
		if ((TEXTBOX[i] = (t_textbox *)malloc(sizeof(t_textbox))) == NULL)
			error(1);
		if ((TEXTBOX[i]->value = (char *)malloc(sizeof(char) * 7)) == NULL)
			error(1);
		if ((TEXTBOX[i]->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
			error(1);
		TEXTBOX[i]->edited = 0;
		TEXTBOX[i]->surface = NULL;
		TEXTBOX[i]->bmp = NULL;
		TEXTBOX[i]->nature = TXB;
		i++;
	}
}

void	gui_textbox_value_clear(t_textbox *textbox, int len)
{
	int i;

	i = 0;
	while (i < len)
		textbox->value[i++] = ' ';
	textbox->value[i] = '\0';
	textbox->vlen = 0;
}

void		gui_textbox_get_len(t_textbox *textbox)
{
	if (ft_strstr(textbox->tag, "__X") || ft_strstr(textbox->tag, "__Y")
		|| ft_strstr(textbox->tag, "__Z"))
		textbox->maxlen = 6;
	if (ft_strstr(textbox->tag, "_AX") || ft_strstr(textbox->tag, "_AY")
		|| ft_strstr(textbox->tag, "_AZ"))
		textbox->maxlen = 4;
	if (ft_strstr(textbox->tag, "__R") || ft_strstr(textbox->tag, "__G")
		|| ft_strstr(textbox->tag, "__B") || ft_strstr(textbox->tag, "__A"))
		textbox->maxlen = 3;
	if (ft_strstr(textbox->tag, "RFR"))
		textbox->maxlen = 5;
	if (ft_strstr(textbox->tag, "RFL"))
		textbox->maxlen = 3;
}

void	gui_textbox_set_halign(t_textbox *textbox)
{
	t_gui	*gui;

	gui = get_gui();
	if (textbox->dest.x == GUI_ALIGN_LEFT)
		textbox->dest.x = 50;
	else if (textbox->dest.x == GUI_ALIGN_MID)
		textbox->dest.x = (GUI_WIDTH / 2) - (textbox->dest.w / 2) + 10;
	else if (textbox->dest.x == GUI_ALIGN_RIGHT)
		textbox->dest.x = GUI_WIDTH - (textbox->dest.w + 20);
	else
		textbox->dest.x = textbox->dest.x;
}

void	gui_textbox_set(t_textbox *textbox)
{
	t_gui	*gui;

	gui = get_gui();
	textbox->dest.w = textbox->maxlen * (gui->dest.w / 32);
	textbox->dest.h = DEF->txb_h;
	textbox->dest.y += BLOCK[textbox->p]->dest.y;
	gui_textbox_set_halign(textbox);
}

void	gui_textbox_create_all(t_gui *gui)
{
	int i;
	int id;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				if (WIDGET == TEXTBOX[i])
					gui_widget_texture_get_bmp(TEXTBOX[i], "textbox_black.bmp");
				else
					gui_widget_texture_get_bmp(TEXTBOX[i], "textbox_white.bmp");
				gui_widget_display(TEXTBOX[i]);
				gui_widget_draw_in_line(TEXTBOX[i]->dest, 1, "black");
				event_textbox_edit(gui, TEXTBOX[i], "black");

				i++;
			}
			id++;
		}
	}
}

void	gui_textbox_build(t_gui *gui)
{
	gui_textbox_create_all(gui);

}
