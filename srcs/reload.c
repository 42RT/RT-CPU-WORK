/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 03:33:32 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/16 03:33:37 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <parser.h>
#include <stdlib.h>

void		delete_all_obj(t_env *e)
{
	t_obj	*act;
	t_obj	*next;

	act = e->obj;
	while (act)
	{
		next = act->next;
		free(act);
		act = next;
	}
	e->obj = 0;
}

void		delete_all_lights(t_env *e)
{
	t_light	*act;
	t_light	*next;

	act = e->light;
	while (act)
	{
		next = act->next;
		free(act);
		act = next;
	}
	e->light = 0;
}

void		reload(t_env *e)
{
	int		thread_ret;
	e->worker_stop = 1;
	SDL_WaitThread(e->worker, &thread_ret);
	delete_all_obj(e);
	delete_all_lights(e);
	parse(e, e->av[1]);
	if (e->set->verbose)
		print_debug(e);
	if (!libxmlx_reload(e->gfx, e->set->width, e->set->height, BUFF_NB))
		exit (1);
	loading_bar(e, 0, int_to_tcolor(0x1010A0), int_to_tcolor(0));
	ft_render(e);
//	if (e->set->preview)
//		ft_aff_quick(e, e->obj);
//	ft_aff(e, e->obj);
}
