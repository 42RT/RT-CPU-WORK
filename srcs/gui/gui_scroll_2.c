/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_scroll_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 17:32:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

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

void	gui_scroll_open(t_gui *gui, t_scroll *scroll)
{
	if (WIDGET)
		event_widget_deselect(gui);
	WIDGET = scroll;
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
