/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 21:02:17 by jrouilly          #+#    #+#             */
/*   Updated: 2017/04/27 15:47:28 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>

int				get_pos(int *map, int res, int *nb)
{
	int		pos;
	int		try_nb;

	try_nb = RAND_TRY;
	pos = rand() % res;
	while (!map[pos])
	{
		if (try_nb-- > 0)
			pos = rand() % res;
		else
		{
			++pos;
			pos %= res;
		}
	}
	--*nb;
	map[pos] = 0;
	return (pos);
}

t_obj			*get_shorter_compose(t_obj *obj, float *dst, t_obj *res)
{
	t_obj	*compose_first;

	while (obj)
	{
		if (obj->dst < *dst && obj->dst > 0.42)
		{
			*dst = obj->dst;
			res = obj;
		}
		compose_first = obj->compose;
		if (obj->compose)
			res = get_shorter_compose(obj->compose, dst, res);
		obj->compose = compose_first;
		obj = obj->next;
	}
	return (res);
}

t_obj			*get_shorter(t_obj *obj)
{
	t_obj			*compose_first;
	float			dst;
	t_obj			*res;

	dst = 1e8;
	res = 0;
	while (obj)
	{
		if (obj->dst < dst && obj->dst > 0.42)
		{
			dst = obj->dst;
			res = obj;
		}
		compose_first = obj->compose;
		if (obj->compose)
			res = get_shorter_compose(obj->compose, &dst, res);
		obj->compose = compose_first;
		obj = obj->next;
	}
	return (res);
}

t_color			safe_reflect_color(t_env *e, t_ray_data *d, unsigned int deph)
{
	t_color		c;
	t_vector	save_o;
	t_vector	save_v;
	t_vector	*arg[2];

	vec_cpy(d->o, &save_o);
	vec_cpy(d->v, &save_v);
	arg[0] = d->o;
	arg[1] = reflect_vector(d->shorter, d->o, d->v, &(d->n));
	c = new_ray(e, arg, d->start, deph);
	vec_cpy(&save_o, d->o);
	vec_cpy(&save_v, d->v);
	c.a = 255;
	return (c);
}

t_color			safe_refract_color(t_env *e, t_ray_data *d, unsigned int deph)
{
	t_color		c;
	float		refract;
	t_vector	save_o;
	t_vector	save_v;
	t_vector	*arg[2];

	vec_cpy(d->o, &save_o);
	vec_cpy(d->v, &save_v);
	refract = e->last_refract;
	e->last_refract = d->shorter->refract_ind;
	e->inside_obj = 0;
	arg[0] = d->o;
	arg[1] = refract_vector(d->v, d->o, refract, d->shorter);
	c = new_ray(e, arg, d->start, deph);
	e->last_refract = 1;
	vec_cpy(&save_o, d->o);
	vec_cpy(&save_v, d->v);
	c.a = 255;
	return (c);
}
