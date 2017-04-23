/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 18:13:36 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 17:32:04 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_param_build(t_gui *gui)
{
	gui_param_scroll_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_textbox_create_all(gui);
	gui_param_gauge_create_all(gui);
	gui_param_text_build(gui);
}

void	gui_param_open(t_gui *gui)
{
	if (gui->widget_active)
		event_widget_deselect(gui);
	gui->widget_active = PARAM;
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_build(gui);
	PARAM->active = 1;
}

void	gui_param_close(t_gui *gui)
{
	gui->widget_active = NULL;
	PARAM->active = 0;
	gui_main_refresh(gui);
}

void	gui_param_toggle(t_gui *gui)
{
	if (PARAM->active == 1)
		gui_param_close(gui);
	else
		gui_param_open(gui);
}

void	gui_param_refresh(t_gui *gui)
{
	gui->widget_active = PARAM;
	gui_button_selected(gui, BLOCK[9]->button[0]);
	gui_param_get_bmp_n_display(gui);
	gui_param_scroll_create_all(gui);
	gui_param_textbox_create_all(gui);
	gui_param_checkbox_create_all(gui);
	gui_param_gauge_create_all(gui);
	gui_param_text_build(gui);
}
