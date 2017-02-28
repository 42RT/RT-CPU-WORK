/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_primitive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 14:22:47 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/08 14:48:36 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	trace_paraboloid(t_obj *obj, t_vector o, t_vector v)
{
	t_equation	eq;
	t_vector	dir;
	t_vector	point;
	float		m;

	dir.x = 0;
	dir.y = -1;
	dir.z = 0;
	rotate_vector2(&o, &obj->ang);
	rotate_vector2(&v, &obj->ang);
	sub_vector(&o, &obj->pos);
	eq.a = vec_dot(&v, &v) - vec_dot(&v, &dir) * vec_dot(&v, &dir);
	eq.b = 2 * vec_dot(&v, &o) - vec_dot(&v, &dir) * (vec_dot(&o, &dir) + 2 * obj->size);
	eq.c = vec_dot(&o, &o) - vec_dot(&o, &dir) * (vec_dot(&o, &dir) + 4 * obj->size);
	eq.delta = eq.b * eq.b - 4 * eq.a * eq.c;
	eq.obj = obj;
	eq.v = v;
	eq.o = o;
	obj->dst = solve_equation(&eq);
	point.x = v.x * obj->dst + o.x;
	point.y = v.y * obj->dst + o.y;
	point.z = v.z * obj->dst + o.z;
	m = vec_dot(&point, &dir);
	obj->n.x = point.x - dir.x * (m + obj->size);
	obj->n.y = point.y - dir.y * (m + obj->size);
	obj->n.z = point.z - dir.z * (m + obj->size);
}

void	paraboloid_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	t_vector	not_ang;
	float		k;

	(void)o;
	not_ang.x = -obj->ang.x;
	not_ang.y = -obj->ang.y;
	not_ang.z = -obj->ang.z;
	n->x = obj->n.x;
	n->y = obj->n.y;
	n->z = obj->n.z;
	k = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	n->x /= k;
	n->y /= k;
	n->z /= k;
	rotate_vector2(n, &not_ang);
}
