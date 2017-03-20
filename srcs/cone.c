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
	t_vector	dir;
	t_vector	point;
	float		a;

	dir.x = 0;
	dir.y = 0;
	dir.z = 1;
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
	point.z = v.z * obj->dst + o.z;
	normalize(&point);
	a = tan(vec_dot(&dir, &point));
	obj->n.x = 2 * point.x;
	obj->n.y = 2 * point.y;
	obj->n.z = -2 * point.z * a * a;
}

void		cone_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	float		k;
	t_vector	not_ang;

	(void)o;
	not_ang.x = -obj->ang.x;
	not_ang.y = -obj->ang.y;
	not_ang.z = -obj->ang.z;
	*n = obj->n;
	k = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	n->x /= k;
	n->y /= k;
	n->z /= k;
	rotate_vector2(n, &not_ang);
}
