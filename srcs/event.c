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

#include <rt.h>

void		rt_exit(t_env *env, t_gui *gui)
{
	SDL_DestroyRenderer(env->img);
	SDL_DestroyWindow(env->win);
	SDL_DestroyRenderer(gui->img);
	SDL_DestroyWindow(gui->win);
	SDL_Quit();
	exit(1);
}

static int	event_keydown(SDL_Event event, t_env *env, t_gui *gui)
{
	if (event.key.keysym.sym == SDLK_ESCAPE)
		rt_exit(env, gui);
	return (0);
}

void		button_perform_action(t_env *env, t_gui *gui, char *action)
{
	if (ft_strstr(action, "DEL") != NULL)
		return;
	else if (ft_strstr(action, "SAVE") != NULL)
		return;
	else if (ft_strstr(action, "APPLY") != NULL)
		return;
	else if (ft_strstr(action, "PARAM") != NULL)
		return;
	else if (ft_strstr(action, "HELP") != NULL)
		return;
	else if (ft_strstr(action, "EXIT") != NULL)
		rt_exit(env, gui);
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

void		event_textbox_deselect(t_gui *gui)
{
	t_textbox *tmp;
	// save value
	tmp = gui->textbox_selected;
	gui->textbox_selected = NULL;
	gui_textbox_get_bmp(gui, tmp);
	gui_textbox_display(gui, tmp);
}

void		event_textbox_select(t_gui *gui, t_textbox *textbox)
{
	if (textbox == gui->textbox_selected)
		event_textbox_deselect(gui);
	else
	{
		if (gui->textbox_selected != NULL)
			event_textbox_deselect(gui);
		gui->textbox_selected = textbox;
	}
	gui_textbox_get_bmp(gui, textbox);
	gui_textbox_display(gui, textbox);
	SDL_RenderPresent(gui->img);
}

int			event_is_textbox(SDL_Event event, t_gui *gui)
{
	int id;
	int i;

	id = 0;
	while (id < GUI_CONTAINER_TOTAL_NB)
	{
		if (BLOCK[id]->textbox == NULL)
			id++;
		else
		{
			i = 0;
			while (i < BLOCK[id]->textbox_qt)
			{
				if ((event.button.x >= TEXTBOX[i]->dest.x) &&
				(event.button.x <= TEXTBOX[i]->dest.x + TEXTBOX[i]->dest.w) &&
				(event.button.y >= TEXTBOX[i]->dest.y) &&
				(event.button.y <= TEXTBOX[i]->dest.y + TEXTBOX[i]->dest.h))
				{
					printf("EVENT : TEXTBOX [%d][%d]\n", id, i);
					event_textbox_select(gui, TEXTBOX[i]);
					return (1);
				}
				i++;
			}
			id++;
		}
	}
	return (0);
}


void		event_mouse_click(SDL_Event event, t_env *env, t_gui *gui)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		if (!event_is_button(event, env, gui))
			event_is_textbox(event, gui);
}


int			event(SDL_Event event, t_env *env)
{
	t_gui *gui;

	gui = get_gui();
	if (event.type == SDL_WINDOWEVENT)
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			rt_exit(env, gui);
	}
	else if (event.type == SDL_KEYDOWN)
		event_keydown(event, env, gui);
	else if (event.type == SDL_MOUSEBUTTONDOWN)
		event_mouse_click(event, env, gui);
	return (0);
}
