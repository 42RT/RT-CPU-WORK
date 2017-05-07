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

int			init_th_data(t_th_data *data, t_env *e, int nb)
{
	data.e = e;
	data.nb = nb;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (0);
}

int			ft_aff_multithread(t_env *e)
{
	t_th_data	d;

	d.th_nb = init_th_data(d, e, e->set->width * e->set->height);
	d.res = d.nb;
	e->render_progression = 0;
	d.map = init_map(d.res);
	launch_threads(&d);
	while (d.nb)
	{
		if (*(e->worker_stop))
		{
			while (d.th_nb > 0)
				;
			print_percentage(-1);
			return (0);
		}
		e->render_progression = 100.0 - ((d.nb * 100) / d.res);
		print_percentage((int)e->render_progression);
	}
	e->remaining = 0;
	while (d.th_nb > 0)
		;
	ft_printf("\rRendering finished !\n");
	free(d.map);
	return (1);
}

int			ft_aff_multithread_line(t_env *e)
{
	t_th_data	data;

	data.th_nb = init_th_data(d, e, e->set->height);
	data.map = init_map(e->set->width * e->set->height);
	launch_threads_line(&data);
	while (data.nb)
	{
		if (*(e->worker_stop))
		{
			while (data.th_nb > 0)
				;
			print_percentage(-1);
			return (0);
		}
		e->render_progression = 100.0 - ((data.nb * 100) / e->set->height);
		print_percentage((int)e->render_progression);
	}
	e->remaining = 0;
	while (data.th_nb > 0)
		;
	ft_printf("\rRendering finished !\n");
	free(data.map);
	return (1);
}

void		free_env(t_env *e)
{
	destroy_obj_list(e->obj);
	free(e);
}

void		ft_aff_rand(t_th_data *a, t_env *e)
{
	int		pos;

	srand(time(NULL));
	while (a->nb > 0 && !*(e->worker_stop))
	{
		pos = rand() % a->res;
		while (!a->map[pos] && a->nb)
		{
			++pos;
			if (pos >= a->res)
				pos = 0;
		}
		if (a->nb)
		{
			a->map[pos] = 0;
			e->y = pos / e->set->width;
			e->x = pos % e->set->width;
			fill_pixel(e, e->obj);
			while (pthread_mutex_lock(&(a->mutex)) != 0)
				;
			if (!a->nb)
			{
				pthread_mutex_unlock(&(a->mutex));
				free_env(e);
				return ;
			}
			--a->nb;
			pthread_mutex_unlock(&(a->mutex));
		}
	}
	free_env(e);
}

void		ft_aff_line(t_th_data *a, t_env *e)
{
	int		y;

	while (a->nb > 0 && e && !*(e->worker_stop))
	{
		while (pthread_mutex_lock(&(a->mutex)) != 0)
			;
		if (!a->nb)
		{
			pthread_mutex_unlock(&(a->mutex));
			free_env(e);
			return ;
		}
		y = a->nb;
		--a->nb;
		pthread_mutex_unlock(&(a->mutex));
		e->y = e->set->height - y;
		e->x = -1;
		while (++e->x < e->set->width)
			fill_pixel(e, e->obj);
	}
	free_env(e);
}
