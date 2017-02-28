/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 16:20:34 by rfriscca          #+#    #+#             */
/*   Updated: 2017/02/15 16:49:42 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	cube_normale(t_vector *n, t_vector *o, t_obj *obj)
{
	t_vector	v;

	v.x = o->x - obj->pos.x;
	v.y = o->y - obj->pos.y;
	v.z = o->z - obj->pos.z;
	if ((v.x > obj->cap2 - EPS && v.x < obj->cap2 + EPS) ||
			(v.x > obj->cap1 - EPS && v.x < obj->cap1 + EPS))
	{
		n->x = 1;
		n->y = 0;
		n->z = 0;
	}
	if ((v.y > obj->cap2 - EPS && v.y < obj->cap2 + EPS) ||
			(v.y > obj->cap1 - EPS && v.y < obj->cap1 + EPS))
	{
		n->x = 0;
		n->y = 1;
		n->z = 0;
	}
	if ((v.z > obj->cap2 - EPS && v.z < obj->cap2 + EPS) ||
			(v.z > obj->cap1 - EPS && v.z < obj->cap1 + EPS))
	{
		n->x = 0;
		n->y = 0;
		n->z = 1;
	}
}

void	trace_cube(t_obj *obj, t_vector o, t_vector v)
{
	float		t;
	float		t1;
	int			save;
	t_equation	eq;

	sub_vector(&o, &obj->pos);
	if (obj->cap1 > obj->cap2)
	{
		save = obj->cap1;
		obj->cap1 = obj->cap2;
		obj->cap2 = save;
	}
	if (v.x >= 0)
	{
		obj->x1 = (obj->cap1 - o.x) / v.x;
		obj->x2 = (obj->cap2 - o.x) / v.x;
	}
	else
	{
		obj->x1 = (obj->cap2 - o.x) / v.x;
		obj->x2 = (obj->cap1 - o.x) / v.x;
	}
	if (v.y >= 0)
	{
		t = (obj->cap1 - o.y) / v.y;
		t1 = (obj->cap2 - o.y) / v.y;
	}
	else
	{
		t = (obj->cap2 - o.y) / v.y;
		t1 = (obj->cap1 - o.y) / v.y;
	}
	if (obj->x1 > t1 || t > obj->x2)
		obj->dst = -1;
	else
	{
		if (t > obj->x1)
			obj->x1 = t;
		if (t1 < obj->x2)
			obj->x2 = t1;
		if (v.z >= 0)
		{
			t = (obj->cap1 - o.z) / v.z;
			t1 = (obj->cap2 - o.z) / v.z;
		}
		else
		{
			t = (obj->cap2 - o.z) / v.z;
			t1 = (obj->cap1 - o.z) / v.z;
		}
		if (obj->x1 > t1 || t > obj->x2)
			obj->dst = -1;
	}
	if (t > obj->x1)
		obj->x1 = t;
	if (t1 < obj->x2)
		obj->x2 = t1;
	eq.x1 = obj->x1;
	eq.x2 = obj->x2;
	eq.obj = obj;
	eq.v = v;
	eq.o = o;
	eq.delta = 1;
	if (obj->dst == -1)
	{
		obj->dst = solve_equation(&eq);
		obj->dst = 1e8;
	}
	else
		obj->dst = solve_equation(&eq);
/*	obj->x1 = eq.x1;
	obj->x2 = eq.x2;
	if (obj->x1 > (0 + EPS) && obj->x1 < 1e8)
		obj->dst = obj->x1;
	else if (obj->x2 > (0 + EPS) && obj->x2 < 1e8)
		obj->dst = obj->x2;
	else
		obj->dst = 1e8;*/
}
