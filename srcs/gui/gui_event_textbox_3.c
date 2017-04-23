/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_textbox_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_txb_insert_3(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	if (SCCODE == 40 || SCCODE == 88)
	{
		event_widget_deselect(gui);
		gui->txb_action = 0;
	}
	else if (SCCODE == 43)
	{
		event_txb_switch_select(gui, textbox);
		gui->txb_action = 0;
	}
	if (gui->txb_action == 1)
	{
		gui_widget_texture_get_bmp(textbox, "textbox_black.bmp");
		gui_widget_display(textbox);
		event_txb_edit(gui, textbox, "white");
	}
}

void	event_txb_insert_2(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	if (((SCCODE >= 30 && SCCODE <= 39) || (SCCODE >= 89 && SCCODE <= 99))
	&& (textbox->edited == 0))
	{
		event_txb_value_clear(textbox, textbox->maxlen);
		textbox->edited = 1;
	}
	if (SCCODE >= 30 && SCCODE <= 39)
	{
		if (SCCODE == 39)
			event_txb_value_rot(textbox, '0');
		else
			event_txb_value_rot(textbox, SCCODE + 19);
	}
	else if (SCCODE >= 89 && SCCODE <= 98)
	{
		if (SCCODE == 98)
			event_txb_value_rot(textbox, '0');
		else
			event_txb_value_rot(textbox, SCCODE - 40);
	}
	else if (SCCODE == 99 && !ft_strcmp(textbox->tag, "RFR"))
		event_txb_value_rot(textbox, '.');
	event_txb_insert_3(event, gui, textbox);
}

void	event_txb_insert(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	gui->txb_action = 1;
	if (SCCODE == 87 && textbox->reserved == 1)
	{
		if (textbox->value[0] != '-' && textbox->value[0] != ' ')
			event_txb_value_move(textbox);
		textbox->value[0] = ' ';
	}
	else if (SCCODE == 86 && textbox->reserved == 1)
	{
		if (textbox->value[0] != '-' && textbox->value[0] != ' ')
			event_txb_value_move(textbox);
		textbox->value[0] = '-';
	}
	else if (SCCODE == 42)
		event_txb_backspace(textbox);
	else if (SCCODE == 76)
		event_txb_value_clear(textbox, textbox->maxlen);
	event_txb_insert_2(event, gui, textbox);
}

int		event_is_textbox_suite(SDL_Event event, t_gui *gui, int id, int i)
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
	return (0);
}

int		event_is_textbox(SDL_Event event, t_gui *gui)
{
	int	i;

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
		return (event_is_textbox_suite(event, gui, 0, 0));
	return (0);
}
