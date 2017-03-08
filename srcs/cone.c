/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 04:53:12 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/20 15:52:35 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void		trace_cone(t_obj *obj, t_vector o, t_vector v)
{
	t_equation	eq;
	t_vector	point;
	float		height;
	float		radius;

	mod_vector(obj, &o, &v);
	eq.a = pow(v.x, 2) + pow(v.y, 2) - pow((double)obj->size / 700.0, 2)
											* pow(obj->mod, 2) * pow(v.z, 2);
	eq.b = 2 * (o.x * v.x + o.y * v.y - o.z * v.z
				* pow((double)obj->size / 700.0, 2) * pow(obj->mod, 2));
	eq.c = pow(o.x, 2) + pow(o.y, 2) - pow((double)obj->size / 700.0, 2)
											* pow(obj->mod, 2) * pow(o.z, 2);
	eq.delta = pow(eq.b, 2) - 4 * eq.a * eq.c;
	eq.obj = obj;
	eq.o = o;
	eq.v = v;
	obj->dst = solve_equation(&eq);
	point.x = v.x * obj->dst + o.x;
	point.y = v.y * obj->dst + o.y;
	point.z = 0;
	height = v.z * obj->dst + o.z;
	radius = vec_len(&point);
	normalize(&point);
	obj->n.x = point.x * height / radius;
	obj->n.y = point.y * height / radius;
	if (height > 0)
		obj->n.z = radius / height;
	else
		obj->n.z = -radius / height;
}

void		cone_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	float		k;
	t_vector	ang;

	(void)o;
	ang.x = -obj->ang.x;
	ang.y = -obj->ang.y;
	ang.z = 0;
	n->x = obj->n.x;
	n->y = obj->n.y;
	n->z = obj->n.z;
	k = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	n->x /= k;
	n->y /= k;
	n->z /= k;
	rotate_vector2(n, &ang);
}
