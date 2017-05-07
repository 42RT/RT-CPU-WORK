/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:44:31 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/07 03:09:08 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_mouse_wheel(SDL_Event event, t_gui *gui)
{
	if (!event_scroll_mouse_wheel(event, gui))
		return ;
}

void	event_mouse_click(SDL_Event event, t_gui *gui)
{
	t_env	*e;

	e = get_env();
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (!event_is_gauge(event, gui, e))
			if (!event_is_scroll(event, gui))
				if (!event_is_checkbox(event, gui))
					if (!event_is_button(event, gui, 0, 0))
						if (!event_is_textbox(event, gui))
							if (gui->widget_active)
								event_widget_deselect(gui);
	}
}

void	event_mouse_motion(SDL_Event event, t_gui *gui)
{
	t_scroll	*tmp;

	if (WIDGET && *(int *)WIDGET == SCL)
	{
		tmp = WIDGET;
		event_scroll_mouse_over(event, gui, tmp);
	}
}
