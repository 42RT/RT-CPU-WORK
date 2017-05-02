/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 03:16:31 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 03:16:31 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		ft_aff_multithread(t_env *e, t_obj *obj)
{
	t_th_data	data;

	(void)obj;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.res = e->set->width * e->set->height;
	data.nb = data.res;
	e->render_progression = 0;
	data.map = init_map(data.res);
	data.e = e;
	launch_threads(&data);
	while (data.nb)
	{
		if (*(e->worker_stop))
		{
			usleep(50000);
			return;
		}
		e->render_progression = 100.0 - ((data.nb * 100) / data.res);
		print_percentage((int)e->render_progression);
	}
	e->remaining = 0;
	ft_printf("\rRendering finished !\n");
}

void		ft_aff_multithread_line(t_env *e, t_obj *obj)
{
	t_th_data	data;

	(void)obj;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.map = init_map(e->set->width * e->set->height);
	data.nb = e->set->height;
	data.e = e;
	launch_threads_line(&data);
	while (data.nb)
	{
		if (*(e->worker_stop))
		{
			usleep(50000);
			return;
		}
		e->render_progression = 100.0 - ((data.nb * 100) / e->set->height);
		print_percentage((int)e->render_progression);
	}
	e->remaining = 0;
	ft_printf("\rRendering finished !\n");
}
