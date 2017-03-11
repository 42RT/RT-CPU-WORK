/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 21:02:17 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/24 12:49:01 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>

int				get_pos(int *map, int res, int *nb)
{
	int		pos;

	pos = rand() % res;
	while (!map[pos])
	{
		++pos;
		if (pos > res)
			pos = 0;
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

t_color			compute_color(t_env *e, t_obj *obj, unsigned int deph)
{
	t_obj		*start;
	t_vector	v;
	t_vector	o;
	t_vector	*vec[2];
	t_obj		*shorter;

	compute_vector(e, &v);
	start = obj;
	o.x = e->set->cam->pos.x;
	o.y = e->set->cam->pos.y;
	o.z = e->set->cam->pos.z;
	while (obj)
	{
		trace_ray(e, obj, &o, &v);
		obj = obj->next;
	}
	shorter = get_shorter(start);
	e->last_dst = shorter ? shorter->dst : e->set->focus_dst;
	vec[0] = &o;
	vec[1] = &v;
	return (ray_effect(e, vec, start, deph));
}

t_color			safe_reflect_color(t_env *e, t_ray_data *d, unsigned int deph)
{
	t_color		c;
	t_vector	save_o;
	t_vector	save_v;

	vec_cpy(d->o, &save_o);
	vec_cpy(d->v, &save_v);
	c = new_ray(e, d->o, reflect_vector(d->shorter, d->o, d->v, &(d->n)),
				d->start, deph);
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

	vec_cpy(d->o, &save_o);
	vec_cpy(d->v, &save_v);
	refract = e->last_refract;
	e->last_refract = d->shorter->refract_ind;
	e->inside_obj = 0;
	c = new_ray(e, d->o, refract_vector(d->v, d->o, refract, d->shorter),
				d->start, deph);
	e->last_refract = 1;
	vec_cpy(&save_o, d->o);
	vec_cpy(&save_v, d->v);
	c.a = 255;
	return (c);
}

//int				mod_dazzle(t_light *light, int color, t_ray_data *d)
//{
//	float		dot;
//	t_vector	v;
//
//	while (light)
//	{
//		v = normalize(sub_vector(&obj_to_light, o));
//		light = light->next;
//	}
//}

t_color			ray_effect(t_env *e, t_vector *vec[2], t_obj *start,
							unsigned int deph)
{
	t_ray_data	d;
	t_color		color;
	float		dst;

	if (!start)
		return (void_tcolor());
	d.shorter = get_shorter(start);
	if (!d.shorter || d.shorter->dst > 1e7)
		return (void_tcolor());
	color = d.shorter->color;
	translate_vector(vec[0], vec[1], d.shorter->dst);
	dst = d.shorter->dst;
	d.o = vec[0];
	d.v = vec[1];
	d.start = start;
	(d.shorter->normale)(&(d.n), vec[0], d.shorter);
//	color_mix_k(&color, trace_lights(e, d, e->light), 192);
	//color = mod_dazzle(e->lights, color, &d); // passerpar copie ??
	color = trace_lights(e, d, e->light);
	if (--deph > 0 && d.shorter)
	{
//		if (d.shorter->type & (SPHERE | CONE | CYLINDER) || d.shorter->type == CUBE)
//			color = color_attenuate(color, vec_dot_abs(vec[1], &(d.n)));
//		if (d.shorter->type & (SPHERE | CONE | CYLINDER) || d.shorter->type == CUBE)
//			color_add(&color, safe_reflect_color(e, &d, deph), 150);
//		if (d.shorter->type & (SPHERE | CONE | CYLINDER) || d.shorter->type == CUBE)
//			color_mix_k(&color, safe_refract_color(e, &d, deph), d.shorter->refract_k);
//		if (d.shorter->type & (SPHERE | CONE | CYLINDER) || d.shorter->type == CUBE)
//			color_mix_k(&color, safe_reflect_color(e, &d, deph), d.shorter->reflect_k);


		if (d.shorter->refract_k > 0)
			color_mix_k(&color, safe_refract_color(e, &d, deph), d.shorter->refract_k);
		if (d.shorter->reflect_k > 0 && e->inside_obj == 0)
			color_add(&color, safe_reflect_color(e, &d, deph),
								d.shorter->reflect_k);
	}
	e->inside_obj = 0;
	color = mod_light(color, dst, 256);
	(void)dst;
	(void)deph;
	return (color);
}
