/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_gauge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 03:52:34 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_is_posttraitment(t_env *e, t_gui *gui, int i)
{
	if (!CMP(PARAM_GAU->tag, "LUM"))
		e->set->luminosity = PARAM_GAU->active_value;
	if (!CMP(PARAM_GAU->tag, "CON"))
		e->set->contrast = PARAM_GAU->active_value;
	if (!CMP(PARAM_GAU->tag, "SAT"))
		e->set->saturation = PARAM_GAU->active_value;
	if (!CMP(PARAM_GAU->tag, "SAT") || !CMP(PARAM_GAU->tag, "CON")
	|| !CMP(PARAM_GAU->tag, "LUM"))
		posttraitment(e);
}

int		event_is_param_gauge(SDL_Event event, t_gui *gui, t_env *e)
{
	int	i;

	i = 0;
	while (PARAM->gauge_qt > i)
	{
		if ((HIT.x >= PARAM_GAU->dest.x) && (HIT.y >= PARAM_GAU->dest.y) &&
		(HIT.x <= PARAM_GAU->dest.x + PARAM_GAU->dest.w) &&
		(HIT.y <= PARAM_GAU->dest.y + PARAM_GAU->dest.h))
		{
			PARAM_GAU_C->dest.x = event.button.x - (PARAM_GAU_C->dest.w / 2);
			PARAM_GAU->active_value = (PARAM_GAU_C->dest.x - PARAM_GAU->dest.x)
			+ 5;
			PARAM_GAU->active_value = gui_gauge_get_norm(PARAM_GAU);
			event_is_posttraitment(e, gui, i);
			gui_main_refresh(gui);
			return (1);
		}
		i++;
	}
	return (0);
}

int		event_is_gauge(SDL_Event event, t_gui *gui, t_env *e)
{
	if (PARAM && PARAM->active == 1)
		return (event_is_param_gauge(event, gui, e));
	return (0);
}
