/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:38:01 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 03:38:01 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gfx.h>
#include <raytracer.h>

void		ft_render_preview(t_env *e)
{
	usleep(2000);
	if (!e->rendering_preview)
		return ;
	while (e->rendering_preview && !*(e->worker_stop))
	{
		posttraitment(e);
		event_poll(e);
		usleep(32000);
	}
	posttraitment(e);
}

void		ft_render(t_env *e)
{
	int				thread_ret;

	gfx_fill_image(e->gfx->buff[BUFF_NB], e->set->width,
								e->set->height, int_to_tcolor(0));
	*(e->worker_stop) = 0;
	e->worker = SDL_CreateThread(ft_aff, "rt_worker", e);
	ft_render_preview(e);
	while (!*(e->worker_stop) && ((e->render_progression < 100
			&& (e->set->display || e->set->threads > 1))
			|| (e->y < e->set->height && e->x < e->set->width
			&& e->set->display == LEGACY && e->set->threads <= 1)))
	{
		if (!(e->set->display & PROGRESSIVE))
				loading_bar(e, e->render_progression,
							int_to_tcolor(0x1010A0), int_to_tcolor(0));
		else
			posttraitment(e);
		event_poll(e);
		usleep(16000);
	}
	if (!*(e->worker_stop))
		SDL_WaitThread(e->worker, &thread_ret);
	usleep(64000);//////////////// semaphore
	posttraitment(e);
	e->worker = 0;
	*(e->worker_stop) = 1;
}
