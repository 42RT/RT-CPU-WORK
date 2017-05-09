/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 12:56:00 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/23 13:07:29 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

static unsigned int	trace_lights_3_compose(t_obj *obj, float len)
{
	t_obj	*first_compose;

	while (obj)
	{
		if (obj->dst < len && obj->dst > 1)
			return (0);
		first_compose = obj->compose;
		if (obj->compose)
			trace_lights_3_compose(obj->compose, len);
		obj->compose = first_compose;
		obj = obj->next;
	}
	return (1);
}

static void			trace_lights_3_extend(int *ref, t_color *color,
	t_trace_lights_data data, t_ray_data d)
{
	t_env	*e;

	e = get_env();
	if (data.obj->negative == 0)
	{
		trace_ray(e, data.obj, d.o, d.v);
		if (d.shorter->transparency == 0 && data.obj->transparency > 0 &&
			data.obj->dst < data.len && data.obj->dst > EPS)
		{
			*ref = 1;
			color_mix_k(color, d.shorter->color, data.obj->transparency);
			color_mix_k(color, data.obj->color, 255 - data.obj->transparency);
			color_mix_k(color, void_tcolor(), 255 - data.obj->transparency);
		}
		else if (d.shorter->transparency > 0 && data.obj == d.shorter &&
			data.obj->dst < data.len && data.obj->dst > EPS)
		{
			*ref = 1;
			color_mix_k(color, d.shorter->color, data.obj->transparency);
			color_mix_k(color, void_tcolor(), 255 - data.obj->transparency);
		}
		else if (data.obj->dst + EPS < data.len && data.obj->dst > 1)
			*ref = -1;
	}
}

static t_color		trace_lights_3(t_env *e, t_ray_data d, t_vector *v,
									float len)
{
	t_obj				*first_compose;
	int					ref;
	t_color				color;
	t_trace_lights_data	data;

	color = void_tcolor();
	data.obj = e->obj;
	ref = 0;
	d.v = v;
	data.len = len;
	while (data.obj)
	{
		trace_lights_3_extend(&ref, &color, data, d);
		if (ref == -1)
			return (void_tcolor());
		first_compose = data.obj->compose;
		if (data.obj->compose &&
			trace_lights_3_compose(data.obj->compose, len) == 0)
			return (void_tcolor());
		data.obj->compose = first_compose;
		data.obj = data.obj->next;
	}
	if (ref == 1)
		return (color);
	return (d.shorter->color);
}

/*
** data.x = len = distance entre objet -> lumiere
** data.y = refangle = angle entre rayon reflechi + vecteur directeur
** data.z = angle = angle entre rayon lumiere + normale de l'objet
*/

static t_color		trace_lights_2(t_env *e, t_ray_data d, t_light *light)
{
	t_vector	v2;
	t_vector	obj_to_light;
	t_vector	reflect_obj_to_light;
	t_color		color;
	t_vector	data;

	color = void_tcolor();
	obj_to_light = light->pos;
	sub_vector(&obj_to_light, d.o);
	data.x = vec_len(&obj_to_light);
	normalize(&obj_to_light);
	v2 = *d.v;
	not_vec(&v2);
	reflect_obj_to_light = obj_to_light;
	not_vec(&reflect_obj_to_light);
	reflect_obj_to_light = *reflect_vector(d.shorter, d.o,
			&reflect_obj_to_light, &d.n);
	data.y = vec_dot(&v2, &reflect_obj_to_light);
	if ((data.z = vec_dot(&obj_to_light, &d.n)) < 0)
		data.z = -data.z;
	color = trace_lights_3(e, d, &obj_to_light, data.x);
	if (!is_void_tcolor(color))
		return (calc_color(data, color, light));
	return (shadow(d.shorter->color, data));
}

t_color				trace_lights(t_env *e, t_ray_data d, t_light *light)
{
	t_color		color;
	t_color		save_color;
	float		turb;

	turb = turbulence(e->x, e->y, SMOOTH_NOISE);
	color = void_tcolor();
	save_color = d.shorter->color;
	if (d.shorter->texture || d.shorter->procedural || d.shorter->normalmap)
		choose_texture(&d, turb);
	while (light)
	{
		color_mix_k(&color, trace_lights_2(e, d, light), 128);
		light = light->next;
	}
	d.shorter->color = save_color;
	return (color);
}
