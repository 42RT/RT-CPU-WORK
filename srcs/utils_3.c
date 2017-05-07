/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 09:09:08 by jrouilly          #+#    #+#             */
/*   Updated: 2017/05/06 09:09:13 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <raytracer.h>

void		free_env(t_env *e)
{
	destroy_obj_list(e->obj);
	free(e);
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

static void		init_t_ray_data(t_ray_data *d, t_obj *start, t_vector *vec[2])
{
	d->o = vec[0];
	d->v = vec[1];
	d->start = start;
}

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
	translate_vector(vec[0], vec[1], d.shorter->dst);
	dst = d.shorter->dst;
	init_t_ray_data(&d, start, vec);
	(d.shorter->normale)(&(d.n), vec[0], d.shorter);
	color = trace_lights(e, d, e->light);
	if (--deph > 0 && d.shorter)
	{
		if (d.shorter->transparency > 0)
			color_mix_k(&color, safe_refract_color(e, &d, deph),
						d.shorter->transparency);
		if (d.shorter->reflect_k > 0 && e->inside_obj == 0)
			color_add(&color, safe_reflect_color(e, &d, deph),
								d.shorter->reflect_k);
	}
	e->inside_obj = 0;
	return (mod_light(color, dst, 256));
}
