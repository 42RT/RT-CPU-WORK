/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/11 18:29:56 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_button_perform_action_suite(t_gui *gui, char *action, t_env *env)
{
	if (!CMP(action, "APPLY") && gui->action == 0)
	{
		gui_apply_object(gui);
		gui_apply_setting(gui);
		gui_rt_reload_object(env, gui);
	}
	else if (!CMP(action, "PARAM"))
	{
		if (HELP->active == 1)
			gui_help_close(gui);
		gui_param_toggle(gui);
	}
	else if (!CMP(action, "HELP"))
	{
		if (PARAM->active == 1)
			gui_param_close(gui);
		gui_help_toggle(gui);
	}
	else if (!CMP(action, "EXIT"))
		gfx_exit(env->gfx, 0);
}

void	event_button_perform_action(t_gui *gui, char *action)
{
	t_env *e;

	e = get_env();
	if (WIDGET)
		event_widget_deselect(gui);
	if (!CMP(action, "RESET"))
	{
		if (PARAM->active == 1)
			gui_reset(gui, "PARAM");
		else
			gui_reset(gui, "MAIN");
		gui_main_refresh(gui);
	}
	else if (!CMP(action, "SAVE"))
	{
		if (!CMP(e->scene, "scene/.default.rts"))
			ft_printf("DEFAULT CANNOT BE SAVED\n");
		else
		{
			gui_save_object(e);
			ft_printf("SCENE SAVED\n");
		}
	}
	else
		event_button_perform_action_suite(gui, action, e);
}

int		event_is_button(SDL_Event event, t_gui *gui, int id, int i)
{
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->button == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->button_qt)
			{
				if ((event.button.x >= BUTTON[i]->dest.x) &&
				(event.button.x <= BUTTON[i]->dest.x + BUTTON[i]->dest.w) &&
				(event.button.y >= BUTTON[i]->dest.y) &&
				(event.button.y <= BUTTON[i]->dest.y + BUTTON[i]->dest.h))
				{
					event_button_perform_action(gui, BUTTON[i]->action);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}
