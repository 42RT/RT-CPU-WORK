/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_event_button.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rdieulan          #+#    #+#             */
/*   Updated: 2017/05/07 03:38:49 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_button_perform_action_suite(t_gui *gui, char *action, t_env *env)
{
	if (!ft_strcmp(action, "APPLY") && gui->action == 0)
	{
		gui_apply_object(gui);
		gui_apply_setting(gui);
		gui_rt_reload_object(env, gui);
	}
	else if (ft_strstr(action, "PARAM") != NULL)
	{
		if (HELP->active == 1)
			gui_help_close(gui);
		gui_param_toggle(gui);
	}
	else if (ft_strstr(action, "HELP") != NULL)
	{
		if (PARAM->active == 1)
			gui_param_close(gui);
		gui_help_toggle(gui);
	}
	else if (ft_strstr(action, "EXIT") != NULL)
		gfx_exit(env->gfx, 0);
}

void	event_button_perform_action(t_gui *gui, char *action)
{
	t_env *env;

	env = get_env();
	if (WIDGET)
		event_widget_deselect(gui);
	if (ft_strstr(action, "RESET") != NULL)
	{
		gui_pending_action_prevent(gui);
		if (PARAM->active == 1)
			gui_reset(gui, "PARAM");
		else
			gui_reset(gui, "MAIN");
		gui_main_refresh(gui);
	}
	else if (ft_strstr(action, "SAVE") != NULL)
	{
		gui->action = 0;
	}
	else
		event_button_perform_action_suite(gui, action, env);
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
