/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:07:51 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/03 15:42:08 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	trace_floor(t_obj *obj, t_vector o, t_vector v)
{
	float		t;

	sub_vector(&o, &(obj->pos));
	rotate_vector2(&o, &(obj->ang));
	rotate_vector2(&v, &(obj->ang));
	exp_compute(&o, &(obj->exp));
	exp_compute(&v, &(obj->exp));
	t = (obj->pos.y - o.y) / v.y;
	obj->dst = t;
}

void	plane_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	t_vector	not_ang;

	not_ang.x = -obj->ang.x;
	not_ang.y = -obj->ang.y;
	not_ang.z = -obj->ang.z;
	n->x = obj->def.x * sin(o->x * 0.005);
	n->y = -1;
	n->z = obj->def.z * sin(o->z * 0.005);
	normalize(n);
	rotate_vector2(n, &not_ang);
}

void	neg_floor(t_obj *obj, t_equation *eq)
{
	t_vector	point;
	t_vector	n;

	plane_normale(&n, &eq->o, obj);
	if (eq->delta >= 0)
	{
		point.x = eq->v.x * eq->x1 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x1 + eq->o.y - obj->pos.y;
		point.z = eq->v.z * eq->x1 + eq->o.z - obj->pos.z;
		if (vec_dot(&point, &n) > 0)
			eq->x1 = 1e8;
		point.x = eq->v.x * eq->x2 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x2 + eq->o.y - obj->pos.y;
		point.z = eq->v.z * eq->x2 + eq->o.z - obj->pos.z;
		if (vec_dot(&point, &n) > 0)
			eq->x2 = 1e8;
	}
}

void	neg_floor_fill(t_obj *obj, t_equation *eq)
{
	t_vector	point;

	neg_floor(obj, eq);
	if (eq->delta >= 0 && eq->obj->type & SPHERE)
	{
		trace_floor(obj, eq->o, eq->v);
		sub_vector(&eq->o, &(obj->pos));
		rotate_vector2(&eq->o, &(obj->ang));
		rotate_vector2(&eq->v, &(obj->ang));
		point.x = eq->v.x * obj->dst + eq->o.x;
		point.y = eq->v.y * obj->dst + eq->o.y;
		point.z = eq->v.z * obj->dst + eq->o.z;
		if (vec_len(&point) > eq->obj->size)
			obj->dst = 1e8;
	}
	else if (eq->delta >= 0 && eq->obj->type & CYLINDER)
	{
		trace_floor(obj, eq->o, eq->v);
		sub_vector(&eq->o, &(obj->pos));
		rotate_vector2(&eq->o, &(obj->ang));
		rotate_vector2(&eq->v, &(obj->ang));
		point.x = eq->v.x * obj->dst + eq->o.x;
		point.y = eq->v.y * obj->dst + eq->o.y;
		point.z = 0;
		if (vec_len(&point) > eq->obj->size)
			obj->dst = 1e8;
	}
	else
		obj->dst = 1e8;
}
