/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:02:12 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/14 12:30:51 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	trace_sphere(t_obj *obj, t_vector o, t_vector v)
{
	t_equation	eq;

	sub_vector(&o, &(obj->pos));
	exp_compute(&o, &(obj->exp));
	exp_compute(&v, &(obj->exp));
	eq.a = powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2);
	eq.b = -2 * (((-o.x) * v.x)
			+ ((-o.y) * v.y)
			+ ((-o.z) * v.z));
	eq.c = powf(o.x, 2) + powf(o.y, 2) + powf(o.z, 2) - powf(obj->size, 2);
	eq.delta = powf(eq.b, 2) - 4 * eq.a * eq.c;
	eq.obj = obj;
	eq.v = v;
	eq.o = o;
	obj->dst = solve_equation(&eq);
	obj->n.x = v.x * obj->dst + o.x;
	obj->n.y = v.y * obj->dst + o.y;
	obj->n.z = v.z * obj->dst + o.z;
}

void	sphere_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	float	k;

	(void)o;
	n->x = obj->n.x;
	n->y = obj->n.y;
	n->z = obj->n.z;
	k = sqrt(n->x * n->x + n->y * n->y + n->z * n->z);
	n->x /= k;
	n->y /= k;
	n->z /= k;
}

void	neg_sphere(t_obj *obj, t_equation *eq)
{
	t_vector	point;

	if (eq->delta >= 0)
	{
		point.x = eq->v.x * eq->x1 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x1 + eq->o.y - obj->pos.y;
		point.z = eq->v.z * eq->x1 + eq->o.z - obj->pos.z;
		if (vec_len(&point) < obj->size)
			eq->x1 = 1e8;
		point.x = eq->v.x * eq->x2 + eq->o.x - obj->pos.x;
		point.y = eq->v.y * eq->x2 + eq->o.y - obj->pos.y;
		point.z = eq->v.z * eq->x2 + eq->o.z - obj->pos.z;
		if (vec_len(&point) < obj->size)
			eq->x2 = 1e8;
	}
}
