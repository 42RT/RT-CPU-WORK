/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/23 18:08:10 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/30 16:45:33 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	trace_square(t_obj *obj, t_vector o, t_vector v)
{
	float		t;
	float		x;
	float		z;

	sub_vector(&o, &(obj->pos));
	rotate_vector2(&o, &(obj->ang));
	rotate_vector2(&v, &(obj->ang));
	exp_compute(&o, &(obj->exp));
	exp_compute(&v, &(obj->exp));
	t = -o.y / v.y;
	x = t * v.x + o.x;
	z = t * v.z + o.z;
	obj->dst = -1;
	if (fabs(x) < obj->size && fabs(z) < obj->size)
		obj->dst = t;
}

void	square_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	(void)o;
	n->x = 0;
	n->y = -1;
	n->z = 0;
	rotate_vector2(n, &(obj->ang));
}
