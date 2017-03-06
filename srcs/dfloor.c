/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfloor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:07:59 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/30 16:44:16 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	trace_dfloor(t_obj *obj, t_vector o, t_vector v)
{
	float		t;
	float		x;
	float		z;

	sub_vector(&o, &(obj->pos));
	rotate_vector2(&o, &(obj->ang));
	rotate_vector2(&v, &(obj->ang));
	exp_compute(&o, &(obj->exp));
	exp_compute(&v, &(obj->exp));
	obj->color = obj->color2;
	t = (obj->pos.y - o.y) / v.y;
	x = t * v.x + o.x;
	z = t * v.z + o.z;
	if (((unsigned int)((x / obj->size) - (x < 0)) % 2)
		!= ((unsigned int)((z / obj->size) - (z < 0)) % 2))
		obj->color = obj->color3;
	obj->dst = t;
}

void	dplane_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	n->x = obj->def.x * sin(o->x * 0.005);
	n->y = -1;
	n->z = obj->def.z * sin(o->z * 0.005);
	normalize(n);
	rotate_vector2(n, &(obj->ang));
}
