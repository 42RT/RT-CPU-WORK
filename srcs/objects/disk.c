/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/20 17:50:17 by jrouilly          #+#    #+#             */
/*   Updated: 2014/12/20 17:50:18 by jrouilly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>
#include <math.h>

void	trace_disk(t_obj *obj, t_vector o, t_vector v)
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
	t = -o.y / v.y;
	x = t * v.x + o.x;
	z = t * v.z + o.z;
	obj->dst = -1;
	if (sqrt(pow(x, 2) + pow(z, 2)) < obj->size)
		obj->dst = t;
}

void	disk_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	(void)o;
	(void)obj;
	n->x = 0;
	n->y = -1;
	n->z = 0;
}
