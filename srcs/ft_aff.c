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
#include <libxmlx.h>
#include <raytracer.h>

void		ft_aff(t_env *e, t_obj *obj)
{
	if (e->set->display == PROGRESSIVE)
	{
		ft_aff_random(e, obj, DEF_MULTITHREAD);
		return ;
	}
	else if (e->set->threads > 1)
	{
		ft_aff_multithread(e, obj);
		return ;	
	}
	e->y = 0;
	while (e->y < e->set->height)
	{
		e->x = 0;
		while (e->x < e->set->width)
		{
			fill_pixel(e, obj);
			++e->x;
		}
		++e->y;
		change_cam(e);
		load_add_line(e->load_bar, (e->y * 200 - 1) / e->set->height, 0x1010A0);
		libxmlx_display_image(e->gfx, e->set->width / 2 - 102,
								e->set->height / 2 - 7, e->load_bar);
		event_poll(e);
	}
	init_bar(e->load_bar, 0x1010A0, 0x000000);
	libxmlx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
}

void		ft_aff_quick(t_env *e, t_obj *obj)
{
	unsigned int	color;

	e->y = 0;
	while (e->y < e->set->height)
	{
		e->x = 0;
		while (e->x < e->set->width)
		{
			color = compute_color(e, obj, e->set->deph);
			libxmlx_pixel_put_to_image(e->gfx->buff[e->gfx->act],
										(int)e->x, (int)e->y, color);
			e->x += 2;
		}
		e->y += 2;
		event_poll(e);
	}
	libxmlx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
}

void		ft_aff_random(t_env *e, t_obj *obj, int multithread)
{
	int				*map;
	int				nb;
	int				res;
	int				pos;
	int				i;

	if (e->set->threads > 1 && multithread)
	{
		ft_aff_multithread(e, e->obj);
		return ;
	}
	res = e->set->width * e->set->height;
	map = init_map(res);
	nb = res;
	i = 0;
	while (nb > 0)
	{
		pos = get_pos(map, res, &nb);
		e->y = pos / e->set->width;
		e->x = pos % e->set->width;
		fill_pixel(e, obj);
		if (!(++i % 2000))
			expose_hook(e);
	}
	ft_printf("Rendering finished\n");
}

void		ft_aff_rand(t_th_data *a, t_env *e)
{
	int		pos;

	srand(time(NULL));
	while (a->nb > 0)
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

void		ft_aff_multithread(t_env *e, t_obj *obj)
{
	int			i;
	int			j;
	t_th_data	data;

	i = 99;
	j = 0;
	(void)obj;
	data.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	data.res = e->set->width * e->set->height;
	data.nb = data.res;
	data.map = init_map(data.res);
	data.e = e;
	launch_threads(&data);
	while (data.nb)
	{
		++j;
		if (i != (data.nb * 100) / data.res)
		{
			ft_printf("%sRendering: %d", (i != 0 ? "\r" : ""), 100 - i);
			i = (data.nb * 100) / data.res;
		}
		if (e->set->display == PROGRESSIVE)
			libxmlx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);//fonction lente
		else
		{
			load_add_line(e->load_bar, 200 - (data.nb * 200) / data.res, 0x1010A0);
			libxmlx_display_image(e->gfx, (e->set->width >> 1) - 102,
									(e->set->height >> 1) - 7, e->load_bar);
		}
		event_poll(e);
		usleep(10000);
	}
	libxmlx_display_image(e->gfx, 0, 0, e->gfx->buff[e->gfx->act]);
	ft_printf("\nRendering finished\n");
}
