/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 01:45:00 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/21 01:45:00 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <gfx.h>
#include <raytracer.h>

int			ft_aff(void *data)
{
	t_env	*e;
	unsigned int	start;

	e = (t_env *)data;
	if (e->set->preview)
		ft_aff_quick(e, e->obj);
	usleep(64000);
	start = (unsigned int)time(NULL);
	if (e->set->display == (PROGRESSIVE | RANDOM))
		ft_aff_random(e, e->obj, DEF_MULTITHREAD);
	else if (e->set->threads > 1 && e->set->display & RANDOM)
		ft_aff_multithread(e, e->obj);
	else if (e->set->threads > 1)
		ft_aff_multithread_line(e, e->obj);
	else
	{
		e->y = 0;
		while (e->y < e->set->height)
		{
			e->x = 0;
			while (e->x < e->set->width)
			{
				if (*(e->worker_stop))
				{
					usleep(100000);
					return (0);
				}
				fill_pixel(e, e->obj);
				++e->x;
			}
			++e->y;
			change_cam(e);//load_add_line(e->load_bar, (e->y * 200 - 1) / e->set->height, 0x1010A0);1
			e->render_progression = (float)(e->y * 100) / e->set->height;
		}
	}
	usleep(32000);
	print_time(start);
	return (0);
}

void		ft_aff_quick(t_env *e, t_obj *obj)// ecran noir ???
{
	t_color	color;

	e->rendering_preview = 1;
	//reset display
	e->y = 0;
	while (e->y < e->set->height)
	{
		e->x = 0;
		while (e->x < e->set->width)
		{
			if (*(e->worker_stop))
				return;
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
}

void		ft_aff_random(t_env *e, t_obj *obj, int multithread)
{
	int				*map;
	int				res;
	int				pos;

	if (e->set->threads > 1 && multithread)
	{
		ft_aff_multithread(e, e->obj);
		return ;
	}
	res = e->set->width * e->set->height;
	map = init_map(res);
	e->remaining = res;
	while (e->remaining > 0 && !*(e->worker_stop))
	{
		pos = get_pos(map, res, &(e->remaining));
		e->y = pos / e->set->width;
		e->x = pos % e->set->width;
		fill_pixel(e, obj);
		e->render_progression = 100 - ((e->remaining * 100) / res);
	}
	if (!*(e->worker_stop))
		ft_printf("Rendering finished\n");
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
			if (pos > a->res)
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
			--a->nb;
			pthread_mutex_unlock(&(a->mutex));
		}
	}
	free(e);
}

void		ft_aff_line(t_th_data *a, t_env *e)
{
	int		y;

	while (a->nb > 0 && !*(e->worker_stop))
	{
		while (pthread_mutex_lock(&(a->mutex)) != 0)
			;
		y = a->nb;
		--a->nb;
		pthread_mutex_unlock(&(a->mutex));
		e->y = e->set->height - y;
		e->x = -1;
		while (++e->x < e->set->width)
		{
			fill_pixel(e, e->obj);
		}
	}
	free(e);
}
