/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:41:47 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 01:41:48 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <raytracer.h>

static int	thread_aff(void *arg)
{
	t_th_data	*a;
	t_env		*e;

	a = (t_th_data *)arg;
	while (pthread_mutex_lock(&(a->mutex)) != 0)
		;
	++a->th_nb;
	pthread_mutex_unlock(&(a->mutex));
	e = copy_env(a->e);
	ft_aff_rand(a, e);
	while (pthread_mutex_lock(&(a->mutex)) != 0)
		;
	--a->th_nb;
	pthread_mutex_unlock(&(a->mutex));
	return (0);
}

static int	thread_aff_line(void *arg)
{
	t_th_data	*a;
	t_env		*e;

	a = (t_th_data *)arg;
	while (pthread_mutex_lock(&(a->mutex)) != 0)
		;
	++a->th_nb;
	pthread_mutex_unlock(&(a->mutex));
	e = copy_env(a->e);
	ft_aff_line(a, e);
	while (pthread_mutex_lock(&(a->mutex)) != 0)
		;
	--a->th_nb;
	pthread_mutex_unlock(&(a->mutex));
	return (0);
}

void		launch_threads(t_th_data *data)
{
	int			i;
	SDL_Thread	*thread_ptr;

	i = -1;
	while (++i < data->e->set->threads)
	{
		if ((thread_ptr = SDL_CreateThread(thread_aff, "workers", data)) == 0)
		{
			*(data->e->worker_stop) = 1;
			return ;
		}
	}
}

void		launch_threads_line(t_th_data *data)
{
	int			i;
	SDL_Thread	*thread_ptr;

	i = -1;
	while (++i < data->e->set->threads)
	{
		if ((thread_ptr = SDL_CreateThread(thread_aff_line,
											"workers", data)) == 0)
		{
			*(data->e->worker_stop) = 1;
			return ;
		}
	}
}
