/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_checkbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_checkbox_get_state(t_checkbox *checkbox)
{
	t_env	*e;

	e = get_env();
	if (!ft_strcmp(checkbox->tag, "PVW"))
		checkbox->selected = e->set->preview;
	else
		checkbox->selected = 0;
}

void	gui_param_checkbox_enable(t_gui *gui, t_checkbox *checkbox)
{
	if (WIDGET)
		event_widget_deselect(gui);
	WIDGET = checkbox;
	checkbox->selected = 1;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_disable(t_gui *gui, t_checkbox *checkbox)
{
	WIDGET = NULL;
	checkbox->selected = 0;
	gui_main_refresh(gui);
}

void	gui_param_checkbox_toggle(t_gui *gui, t_checkbox *checkbox)
{
	if (checkbox->selected == 1)
		gui_param_checkbox_disable(gui, checkbox);
	else
		gui_param_checkbox_enable(gui, checkbox);
}
