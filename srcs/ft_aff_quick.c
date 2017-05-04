/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_quick.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 07:34:50 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/02 07:34:51 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

int			ft_aff_quick(t_env *e, t_obj *obj)// ecran noir ???
{
	t_color	color;

	if (e->set->threads > 1)
		return (ft_aff_quick_mult(e));
	e->rendering_preview = 1;
	e->y = 0;
	while (e->y < e->set->height)
	{
		e->x = 0;
		while (e->x < e->set->width)
		{
			if (*(e->worker_stop))
				return (e->rendering_preview = 0);
			color = compute_color(e, obj, e->set->deph);
			color.a = 255;
			gfx_pixel_put_to_image(e->gfx->buff[BUFF_NB],
										(int)e->x, (int)e->y, color);
			e->x += 2;
		}
		e->y += 2;
	}
	if (SMOOTHING)
		smooth_quickrender(e);
	e->rendering_preview = 0;
	return (1);
}

int			ft_aff_quick_mult(t_env *e)
{
	t_th_data	data;

	e->rendering_preview = 1;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.map = init_map(e->set->width * e->set->height);
	data.nb = e->set->height;
	data.e = e;
	launch_threads_quick(&data);
	while (data.nb > 0)
	{
		if (*(e->worker_stop))
		{
			usleep(128000);
			e->rendering_preview = 0;
			return (0);
		}
	}
	e->rendering_preview = 0;
	return (1);
}

void		ft_aff_line_quick(t_th_data *a, t_env *e)
{
	int		y;
	t_color	color;

	while (a->nb > 0 && !*(e->worker_stop))
	{
		while (pthread_mutex_lock(&(a->mutex)) != 0)
			;
		y = a->nb;
		a->nb -= 2;
		pthread_mutex_unlock(&(a->mutex));
		e->y = e->set->height - y;
		e->x = 0;
		while (e->x < e->set->width)
		{
			color = compute_color(e, e->obj, 2);
			color.a = 255;
			gfx_pixel_put_to_image(e->gfx->buff[BUFF_NB],
									(int)e->x, (int)e->y, color);
			e->x += 2;
		}
	}
	free(e);
}

static int	thread_aff_quick(void *arg)
{
	t_th_data	*a;
	t_env		*e;

	a = (t_th_data *)arg;
	e = copy_env(a->e);
	ft_aff_line_quick(a, e);
	return (0);
}

void		launch_threads_quick(t_th_data *data)
{
	int			i;
	SDL_Thread	*thread_ptr;

	i = -1;
	while (++i < data->e->set->threads)
	{
		if ((thread_ptr = SDL_CreateThread(thread_aff_quick,
				"workers", data)) == 0)
		{
			*(data->e->worker_stop) = 1;
			return ;
		}
	}
}