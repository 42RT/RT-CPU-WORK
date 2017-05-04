/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_refresher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdieulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:02:34 by rdieulan          #+#    #+#             */
/*   Updated: 2017/01/17 21:29:24 by rdieulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gui.h>

void	gui_rt_reload_object(t_env *e, t_gui *gui)
{
	int	thread_ret;

	*(e->worker_stop) = 1;
	SDL_WaitThread(e->worker, &thread_ret);
	if ((e->set->oldw != e->set->width) || (e->set->oldh != e->set->width))
		gfx_reload(e->gfx, e->set->width, e->set->height, BUFF_NB + 1);
	if (e->set->verbose)
		print_debug(e);
	loading_bar(e, 0, int_to_tcolor(0x0101A0), int_to_tcolor(0));
	ft_render(e);
	SDL_RaiseWindow(e->gfx->win);
	gui_main_refresh(gui);
}

void	gui_rt_reload(t_env *e, t_gui *gui, char *scene)
{
	free(e->av[1]);
	e->av[1] = ft_strdup(scene);
	reload(e);
	SDL_RaiseWindow(e->gfx->win);
	gui_reparse_scroll_value(gui, "ALL", 0, 0);
	gui_reparse_textbox_value(gui, "ALL");
	gui_main_refresh(gui);
}

void	gui_main_refresh(t_gui *gui)
{
	gui_background_get_set_n_display(gui);
	gui_textbox_create_all(gui);
	gui_button_create_all(gui);
	gui_scroll_create_all(gui);
	gui_font_build(gui);
	if (PARAM && PARAM->active)
		gui_param_refresh(gui);
	gui->action = 0;
}

void	gui_reset(t_gui *gui, char *target)
{
	gui_reparse_scroll_value(gui, target, 0, 0);
	gui_reparse_textbox_value(gui, target);
	gui_reset_gauge_value(gui, target);
	gui_reset_checkbox_state(gui, target);
}
