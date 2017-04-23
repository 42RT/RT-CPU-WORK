/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 13:58:16 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 18:03:35 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void		gui_pending_action_prevent(t_gui *gui)
{
	SDL_Surface	*surf;
	SDL_Texture	*bmp;
	SDL_Rect	dest;

	dest.x = 0;
	dest.y = 0;
	dest.w = gui->dest.w;
	dest.h = gui->dest.h;
	gui->action = 1;
	surf = SDL_LoadBMP("./ressources/gui_texture/help_black.bmp");
	if (!surf)
		gui_error(2);
	bmp = SDL_CreateTextureFromSurface(gui->img, surf);
	if (!bmp)
		gui_error(3);
	SDL_SetTextureBlendMode(bmp, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(bmp, 200);
	SDL_RenderCopy(gui->img, bmp, NULL, &dest);
	SDL_DestroyTexture(bmp);
	SDL_FreeSurface(surf);
	SDL_RenderPresent(gui->img);
}

void		event_widget_deselect(t_gui *gui)
{
	if (*(int *)WIDGET == TXB)
		event_txb_deselect(gui);
	else if (*(int *)WIDGET == SCL)
		gui_scroll_toggle(gui, (t_scroll *)gui->widget_active);
}

void		button_perform_action(t_env *env, t_gui *gui, char *action)
{
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
		gui_pending_action_prevent(gui);
		gui_save_object(gui, env);
		gui->action = 0;
	}
	else if (!ft_strcmp(action, "APPLY") && gui->action == 0)
	{
		gui_pending_action_prevent(gui);
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

int			event_is_button(SDL_Event event, t_env *env, t_gui *gui)
{
	int id;
	int i;

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
				if ((event.button.x >= BUTTON[i]->dest.x) &&
				(event.button.x <= BUTTON[i]->dest.x + BUTTON[i]->dest.w) &&
				(event.button.y >= BUTTON[i]->dest.y) &&
				(event.button.y <= BUTTON[i]->dest.y + BUTTON[i]->dest.h))
				{
					printf("EVENT : BUTTON [%d][%d] -> %s\n", id, i,
						BUTTON[i]->action);
					SDL_FlushEvents(SDL_QUIT, SDL_LASTEVENT);
					button_perform_action(env, gui, BUTTON[i]->action);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}

int			event_is_param_checkbox(SDL_Event event, t_gui *gui)
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
			printf("EVENT : PARAM CHECKBOX [%d]\n", i);
			gui_param_checkbox_toggle(gui, PARAM_CBX);
			return (1);
		}
		i++;
	}
	return (0);
}

int			event_is_checkbox(SDL_Event event, t_gui *gui)
{
	if (PARAM && PARAM->active == 1)
		return (event_is_param_checkbox(event, gui));
	// main window checkbox research to be included here
	return (0);
}

int			event_is_param_gauge(SDL_Event event, t_gui *gui)
{
	int	i;

	i = 0;
	while (i < PARAM->gauge_qt)
	{
		if ((event.button.x >= PARAM_GAU->dest.x) &&
		(event.button.x <= PARAM_GAU->dest.x + PARAM_GAU->dest.w) &&
		(event.button.y >= PARAM_GAU->dest.y) &&
		(event.button.y <= PARAM_GAU->dest.y + PARAM_GAU->dest.h))
		{
			printf("EVENT : PARAM GAUGE [%d]\n", i);
			PARAM_GAU_C->dest.x = event.button.x - (PARAM_GAU_C->dest.w / 2);
			PARAM_GAU->active_value = (PARAM_GAU_C->dest.x - PARAM_GAU->dest.x) + 5;
			PARAM_GAU->active_value = gui_gauge_get_norm(PARAM_GAU);
			gui_main_refresh(gui);
			return (1);
		}
		i++;
	}
	return (0);
}

int			event_is_gauge(SDL_Event event, t_gui *gui)
{
	if (PARAM && PARAM->active == 1)
		return (event_is_param_gauge(event, gui));
	// main window gauge research to be included here
	return (0);
}
