/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_button_selected(t_gui *gui, t_button *button)
{
	gui_font_init(gui, "Starjedi", TTF->def_size);
	gui_widget_draw_depth(button->dest, GUI_BTN_DEPTH, "red brick");
	gui_widget_write_txt(button, "red brick");
	TTF_CloseFont(TTF->font);
}

void	gui_button_create_all(t_gui *gui)
{
	int	i;
	int	id;

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
				gui_widget_draw_depth(BUTTON[i]->dest, GUI_BTN_DEPTH, "white");
				i++;
			}
			id++;
		}
	}
}
