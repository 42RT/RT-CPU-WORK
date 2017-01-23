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

void		event_textbox_edit(t_gui *gui, t_textbox *textbox, char *color)
{
	gui_font_init(gui, "Starjedi", 16);
	gui_write_textbox_value(gui, textbox, color);
	TTF_CloseFont(TTF->font);
}

void		event_widget_deselect(t_gui *gui)
{
	t_textbox *tmp;
	// save value
	tmp = gui->widget_active;
	tmp->edited = 0;
	gui->widget_active = NULL;
	gui_textbox_get_bmp(gui, tmp);
	gui_textbox_display(gui, tmp);
	event_textbox_edit(gui, tmp, "black");
}

void		event_textbox_select(t_gui *gui, t_textbox *textbox)
{
	if (textbox == gui->widget_active)
		event_widget_deselect(gui);
	else
	{
		if (gui->widget_active)
			event_widget_deselect(gui);
		gui->widget_active = textbox;
		gui_textbox_get_bmp(gui, textbox);
		gui_textbox_display(gui, textbox);
		textbox->vlen = 0;
		event_textbox_edit(gui, gui->widget_active, "white");
	}
}

void		event_textbox_value_clear(t_textbox *textbox)
{
	textbox->value[1] = ' ';
	textbox->value[2] = ' ';
	textbox->value[3] = ' ';
	textbox->vlen = 0;
}

void		event_textbox_value_rot(t_textbox *textbox, char nb)
{
	if (textbox->value[3] != ' ')
	{
		if (textbox->value[2] != ' ')
		{
			if (textbox->value[1] == ' ')
				textbox->value[1] = textbox->value[2];
			else
				event_textbox_value_clear(textbox);
		}
		textbox->value[2] = textbox->value[3];
	}
	textbox->value[3] = nb;
}

void		event_textbox_insert(SDL_Event event, t_gui *gui, t_textbox *textbox)
{
	if (event.key.keysym.scancode == 40 || event.key.keysym.scancode == 88)
		event_widget_deselect(gui);
	else
	{
		if (event.key.keysym.scancode == 87 || event.key.keysym.scancode == 86)
		{
			if (event.key.keysym.scancode == 87)
				textbox->value[0] = ' ';
			else
				textbox->value[0] = '-';
		}
		else
		{
			if (textbox->edited == 0)
			{
				event_textbox_value_clear(textbox);
				textbox->edited = 1;
			}
			if (event.key.keysym.scancode == 30 || event.key.keysym.scancode == 89)
				event_textbox_value_rot(textbox, '1');
			if (event.key.keysym.scancode == 31 || event.key.keysym.scancode == 90)
				event_textbox_value_rot(textbox, '2');
			if (event.key.keysym.scancode == 32 || event.key.keysym.scancode == 91)
				event_textbox_value_rot(textbox, '3');
			if (event.key.keysym.scancode == 33 || event.key.keysym.scancode == 92)
				event_textbox_value_rot(textbox, '4');
			if (event.key.keysym.scancode == 34 || event.key.keysym.scancode == 93)
				event_textbox_value_rot(textbox, '5');
			if (event.key.keysym.scancode == 35 || event.key.keysym.scancode == 94)
				event_textbox_value_rot(textbox, '6');
			if (event.key.keysym.scancode == 36 || event.key.keysym.scancode == 95)
				event_textbox_value_rot(textbox, '7');
			if (event.key.keysym.scancode == 37 || event.key.keysym.scancode == 96)
				event_textbox_value_rot(textbox, '8');
			if (event.key.keysym.scancode == 38 || event.key.keysym.scancode == 97)
				event_textbox_value_rot(textbox, '9');
			if (event.key.keysym.scancode == 39 || event.key.keysym.scancode == 98)
				event_textbox_value_rot(textbox, '0');
		}
		gui_textbox_get_bmp(gui, textbox);
		gui_textbox_display(gui, textbox);
		event_textbox_edit(gui, textbox, "white");
	}
}

static int	event_keydown(SDL_Event event, t_env *env, t_gui *gui)
{
	//printf("EVENT : KEY = %d\n", event.key.keysym.scancode);
	if (event.key.keysym.sym == SDLK_ESCAPE)
		rt_exit(env, gui);
	if (gui->widget_active)
		event_textbox_insert(event, gui, gui->widget_active);
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
	{
		if (!event_is_button(event, env, gui))
			if(!event_is_textbox(event, gui))
				if (gui->widget_active)
					event_widget_deselect(gui);
	}
}


int			event(SDL_Event event, t_env *env)
{
	t_gui *gui;

	gui = get_gui();
	if (event.type == SDL_WINDOWEVENT)
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			rt_exit(env, gui);
	if (event.type == SDL_KEYDOWN)
		event_keydown(event, env, gui);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		event_mouse_click(event, env, gui);
	SDL_RenderPresent(gui->img);
	return (0);
}
