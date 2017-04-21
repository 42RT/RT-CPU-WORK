#include <gui.h>

void	event_txb_insert(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	int	action;

	action = 1;
	if (SCANCODE == 40 || SCANCODE == 88)
	{
		event_widget_deselect(gui);
		action = 0;
	}
	else if (SCANCODE == 43)
	{
		event_txb_switch_select(gui, textbox);
		action = 0;
	}
	else if (SCANCODE == 87 && textbox->maxlen > 3)
		textbox->value[0] = ' ';
	else if (SCANCODE == 86 && textbox->maxlen > 3)
		textbox->value[0] = '-';
	else if (SCANCODE == 42)
		event_txb_backspace(textbox);
	else if (SCANCODE == 76)
		event_txb_value_clear(textbox, textbox->maxlen);
	else if (SCANCODE >= 30 && SCANCODE <= 39)
	{
		if (textbox->edited == 0)
		{
			event_txb_value_clear(textbox, textbox->maxlen);
			textbox->edited = 1;
		}
		if (SCANCODE == 39)
			event_txb_value_rot(textbox, '0');
		else
			event_txb_value_rot(textbox, SCANCODE + 19);
	}
	else if (SCANCODE >= 89 && SCANCODE <= 99)
	{
		if (textbox->edited == 0)
		{
			event_txb_value_clear(textbox, textbox->maxlen);
			textbox->edited = 1;
		}
		if (SCANCODE == 98)
			event_txb_value_rot(textbox, '0');
		else
			event_txb_value_rot(textbox, SCANCODE - 40);
	}
	else
		action = 0;
	if (action == 1)
	{
		gui_widget_texture_get_bmp(textbox, "textbox_black.bmp");
		gui_widget_display(textbox);
		event_txb_edit(gui, textbox, "white");
		SDL_RenderPresent(gui->img);
	}
}

int		event_is_textbox(SDL_Event event, t_gui *gui)
{
	int	id;
	int	i;

	id = 0;
	if (HELP && HELP->active == 1)
		return (0);
	else if (PARAM && PARAM->active == 1)
	{
		i = 0;
		while (i < PARAM->textbox_qt)
		{
			if ((event.button.x >= PARAM_TXB->dest.x) &&
			(event.button.x <= PARAM_TXB->dest.x + PARAM_TXB->dest.w) &&
			(event.button.y >= PARAM_TXB->dest.y) &&
			(event.button.y <= PARAM_TXB->dest.y + PARAM_TXB->dest.h))
			{
				event_txb_select(gui, PARAM_TXB);
				return (1);
			}
			i++;
		}
	}
	else
	{
		while (id < GUI_CONTAINER_TOTAL_NB)
		{
			if (BLOCK[id]->textbox == NULL)
				id++;
			else
			{
				i = 0;
				while (i < BLOCK[id]->textbox_qt)
				{
					if ((event.button.x >= TEXTBOX[i]->dest.x) &&
					(event.button.x <= TEXTBOX[i]->dest.x + TEXTBOX[i]->dest.w)
					&& (event.button.y >= TEXTBOX[i]->dest.y) &&
					(event.button.y <= TEXTBOX[i]->dest.y + TEXTBOX[i]->dest.h))
					{
						event_txb_select(gui, TEXTBOX[i]);
						return (1);
					}
					i++;
				}
				id++;
			}
		}
	}
	return (0);
}
