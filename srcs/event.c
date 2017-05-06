/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 02:44:21 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 02:44:25 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	event_poll(t_env *e)
{
	while (gfx_poll(e->gfx))
		event(e, e->gfx->event);
}

void	wait_event(t_env *e)
{
	while (gfx_loop(e->gfx))
		event(e, e->gfx->event);
}

static int	event_keydown(SDL_Event event, t_env *env, t_gui *gui)
{
	static int	console_mode = 0;
	int			old;

	old = console_mode;
	if (event.window.windowID == env->gfx->winID)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			gfx_exit(env->gfx, 0);
		if (env->background && (event.key.keysym.sym == SDLK_RETURN
								|| event.key.keysym.sym == SDLK_SPACE))
		{
			env->background = 0;
			gui = gui_init();
			ft_render(env);
		}
		else if (!env->background)
		{
			if (event.key.keysym.sym == SDLK_BACKQUOTE || event.key.keysym.sym == 178)
				console_mode = !console_mode;
			if (console_mode)
				console_mode = rt_console(event.key.keysym.sym, env, !old);
			if (!console_mode)
				gfx_display_image(env->gfx, 0, 0, env->gfx->buff[env->gfx->act]);
		}
	}
	if (gui->widget_active && (event.window.windowID == gui->winID))
		event_txb_insert(event, gui, gui->widget_active);
	return (0);
}

int		event(t_env *env, SDL_Event event)
{
	t_gui *gui;

	gui = get_gui();
	if (event.type == SDL_WINDOWEVENT)
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			gfx_exit(env->gfx, 0);
	if (event.type == SDL_KEYDOWN)
		event_keydown(event, env, gui);
	else
	{
		if (event.window.windowID == gui->winID && gui->action == 0)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
				event_mouse_click(event, gui);
			if (event.type == SDL_MOUSEWHEEL)
				event_mouse_wheel(event, gui);
			if (event.type == SDL_MOUSEMOTION)
				event_mouse_motion(event, gui);
		}
		SDL_RenderPresent(gui->img);
	}
	return (0);
}
