/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_checkbox.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

int		event_is_param_checkbox(SDL_Event event, t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->checkbox_qt)
	{
		if ((event.button.x >= PARAM_CBX->dest.x) &&
		(event.button.x <= PARAM_CBX->dest.x + PARAM_CBX->dest.w) &&
		(event.button.y >= PARAM_CBX->dest.y) &&
		(event.button.y <= PARAM_CBX->dest.y + PARAM_CBX->dest.h))
		{
			gui_param_checkbox_toggle(gui, PARAM_CBX);
			return (1);
		}
		i++;
	}
	return (0);
}

int		event_is_checkbox(SDL_Event event, t_gui *gui)
{
	if (PARAM && PARAM->active == 1)
		return (event_is_param_checkbox(event, gui));
	return (0);
}
