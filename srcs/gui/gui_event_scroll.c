/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_scroll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

int			event_is_scroll_suite(SDL_Event event, t_gui *gui, int id, int i)
{
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->scroll == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->scroll_qt)
			{
				if (SCROLL[i] == gui->widget_active)
					return (gui_scroll_value_select(gui, event, SCROLL[i]));
				if ((event.button.x >= SCROLL_B->dest.x) &&
				(event.button.x <= SCROLL_B->dest.x + SCROLL_B->dest.w) &&
				(event.button.y >= SCROLL_B->dest.y) &&
				(event.button.y <= SCROLL_B->dest.y + SCROLL_B->dest.h))
				{
					gui_scroll_toggle(gui, SCROLL[i]);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}

int			event_is_scroll(SDL_Event event, t_gui *gui)
{
	int	i;

	if (HELP && HELP->active == 1)
		return (0);
	else if (PARAM && PARAM->active == 1)
	{
		i = 0;
		while (i < PARAM->scroll_qt)
		{
			if (PARAM_SCL == gui->widget_active)
				return (gui_scroll_value_select(gui, event, PARAM_SCL));
			if ((event.button.x >= PARAM_SCL_B->dest.x) &&
			(event.button.x <= PARAM_SCL_B->dest.x + PARAM_SCL_B->dest.w) &&
			(event.button.y >= PARAM_SCL_B->dest.y) &&
			(event.button.y <= PARAM_SCL_B->dest.y + PARAM_SCL_B->dest.h))
			{
				gui_scroll_toggle(gui, PARAM_SCL);
				return (1);
			}
			i++;
		}
	}
	else
		return (event_is_scroll_suite(event, gui, 0, 0));
	return (0);
}
