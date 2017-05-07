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

int			ft_aff_std(t_env *e)
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
				print_percentage(-1);
				return (0);
			}
			fill_pixel(e, e->obj);
			++e->x;
		}
		++e->y;
		change_cam(e);
		e->render_progression = (float)(e->y * 100) / e->set->height;
		print_percentage((int)e->render_progression);
	}
	return (1);
}

int			ft_aff(void *data)
{
	t_env			*e;
	unsigned int	start;
	int				ret;

	e = (t_env *)data;
	ret = 1;
	if (e->set->preview)
		ret = ft_aff_quick(e, e->obj);
	usleep(64000);
	start = (unsigned int)time(NULL);
	if (ret && e->set->display == (PROGRESSIVE | RANDOM))
		ret = ft_aff_random(e, e->obj, DEF_MULTITHREAD);
	else if (ret && e->set->threads > 1 && e->set->display & RANDOM)
		ret = ft_aff_multithread(e);
	else if (ret && e->set->threads > 1)
		ret = ft_aff_multithread_line(e);
	else if (ret)
		ret = ft_aff_std(e);
	if (ret)
		print_time(start);
	return (0);
}

void		ft_aff_random_extend(int *map)
{
	print_percentage(-1);
	free(map);
}

int			ft_aff_random(t_env *e, t_obj *obj, int multithread)
{
	int				*map;
	int				res;
	int				pos;

	if (e->set->threads > 1 && multithread)
		return (ft_aff_multithread(e));
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
		print_percentage((int)e->render_progression);
	}
	if (!*(e->worker_stop))
	{
		ft_printf("Rendering finished\n");
		return (1);
	}
	ft_aff_random_extend(map);
	return (0);
}
