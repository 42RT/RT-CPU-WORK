#include <gui.h>

void	gui_reparse_textbox_value(t_gui *gui, char *target)
{
	int i;
	int id;

	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
	{
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
	else if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 0;
		while (i < PARAM->textbox_qt)
		{
			free(PARAM_TXB->value);
			gui_get_textbox_value(PARAM_TXB);
			i++;
		}
	}
}

t_textbox	*gui_textbox_init(void)
{
	t_textbox *textbox;

	if (!(textbox = (t_textbox *)malloc(sizeof(t_textbox))))
		error(1);
	if (!(textbox->txt = (t_txt *)malloc(sizeof(t_txt))))
		error(1);
	textbox->surface = NULL;
	textbox->bmp = NULL;
	textbox->nature = TXB;
	return (textbox);
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
		if ((TEXTBOX[i]->tag = (char *)malloc(sizeof(char) * 3)) == NULL)
			error(1);
		TEXTBOX[i]->edited = 0;
		TEXTBOX[i]->surface = NULL;
		TEXTBOX[i]->bmp = NULL;
		TEXTBOX[i]->nature = TXB;
		i++;
	}
}

void		gui_textbox_get_len(t_textbox *textbox)
{
	char	*tag;

	tag = ft_strdup(textbox->tag);
	if (!ft_strcmp(tag, "__X") || !ft_strcmp(tag, "__Y")
	|| !ft_strcmp(tag, "__Z") || !ft_strcmp(tag, "_CX")
	|| !ft_strcmp(tag, "_CY") || !ft_strcmp(tag, "_CZ"))
		textbox->maxlen = 6;
	if (!ft_strcmp(tag, "_AX") || !ft_strcmp(tag, "_AY")
		|| !ft_strcmp(tag, "_AZ"))
		textbox->maxlen = 4;
	if (!ft_strcmp(tag, "__R") || !ft_strcmp(tag, "__G")
		|| !ft_strcmp(tag, "__B") || !ft_strcmp(tag, "__A")
		|| !ft_strcmp(tag, "RFL"))
		textbox->maxlen = 3;
	if (!ft_strcmp(tag, "RFR"))
		textbox->maxlen = 5;
	free(tag);
}

void	gui_textbox_set_halign(t_textbox *textbox, SDL_Rect dest)
{
	if (textbox->dest.x == GUI_ALIGN_LEFT)
		textbox->dest.x = dest.x + 50;
	else if (textbox->dest.x == GUI_ALIGN_MID)
		textbox->dest.x = ((dest.w + (dest.x * 2.5)) / 2) - (textbox->dest.w / 2) + 10;
	else if (textbox->dest.x == GUI_ALIGN_RIGHT)
		textbox->dest.x = (dest.w + (dest.x * 1.5)) - (textbox->dest.w + 20);
	else
		textbox->dest.x = textbox->dest.x;
}

void	gui_textbox_set(t_textbox *textbox, SDL_Rect dest)
{
	t_gui	*gui;

	gui = get_gui();
	textbox->dest.w = textbox->maxlen * (PARAM->dest.w / 32);
	textbox->dest.h = DEF->txb_h;
	if (textbox->p >= 0)
		textbox->dest.y += BLOCK[textbox->p]->dest.y;
	gui_textbox_set_halign(textbox, dest);
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
				event_txb_edit(gui, TEXTBOX[i], "black");
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
