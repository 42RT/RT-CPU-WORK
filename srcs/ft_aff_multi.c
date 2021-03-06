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

int			ft_aff_multithread(t_env *e)
{
	t_th_data	data;

	data.th_nb = init_th_data(&data, e, e->set->width * e->set->height);
	data.res = data.nb;
	*(e->render_progression) = 0;
	data.map = init_map(data.res);
	launch_threads(&data);
	while (data.nb)
	{
		if (*(e->worker_stop))
		{
			free_threads(&data);
			print_percentage(-1);
			return (0);
		}
		*(e->render_progression) = 100.0 - ((data.nb * 100) / data.res);
		print_percentage((int)*(e->render_progression));
	}
	e->remaining = 0;
	free_threads(&data);
	ft_printf("\rRendering finished !\n");
	return (1);
}

int			ft_aff_multithread_line(t_env *e)
{
	t_th_data	data;

	data.th_nb = init_th_data(&data, e, e->set->height);
	data.map = init_map(e->set->width * e->set->height);
	launch_threads_line(&data);
	while (data.nb)
	{
		if (*(e->worker_stop))
		{
			free_threads(&data);
			print_percentage(-1);
			return (0);
		}
		*(e->render_progression) = 100.0 - ((data.nb * 100) / e->set->height);
		print_percentage(*(e->render_progression));
	}
	e->remaining = 0;
	free_threads(&data);
	ft_printf("\rRendering finished !\n");
	return (1);
}

static void	ft_aff_rand_wait(t_th_data *a)
{
	while (pthread_mutex_lock(&(a->mutex)) != 0)
		;
	if (!a->nb)
	{
		pthread_mutex_unlock(&(a->mutex));
		return ;
	}
	--a->nb;
	pthread_mutex_unlock(&(a->mutex));
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
			ft_aff_rand_wait(a);
		}
	}
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
}
