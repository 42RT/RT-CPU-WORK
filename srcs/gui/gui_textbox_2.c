/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_textbox_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_reparse_textbox_value_suite(t_gui *gui, int id, int i)
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
				free(TEXTBOX[i]->value);
				gui_get_textbox_value(TEXTBOX[i]);
				i++;
			}
			id++;
		}
	}
}

void	gui_reparse_textbox_value(t_gui *gui, char *target)
{
	int	i;

	if (!ft_strcmp(target, "PARAM") || !ft_strcmp(target, "ALL"))
	{
		i = 0;
		while (i < PARAM->textbox_qt)
		{
			free(PARAM_TXB->value);
			gui_get_textbox_value(PARAM_TXB);
			i++;
		}
	}
	if (!ft_strcmp(target, "MAIN") || !ft_strcmp(target, "ALL"))
		gui_reparse_textbox_value_suite(gui, 0, 0);
}

void	gui_textbox_create_all(t_gui *gui)
{
	int	i;
	int	id;

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
