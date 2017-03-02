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
	n->x = 0;
	n->y = 0;
	n->z = 0;
	if ((v.x > obj->cap2 - EPS && v.x < obj->cap2 + EPS) ||
			(v.x > obj->cap1 - EPS && v.x < obj->cap1 + EPS))
		n->x = 1;
	else if ((v.y > obj->cap2 - EPS && v.y < obj->cap2 + EPS) ||
			(v.y > obj->cap1 - EPS && v.y < obj->cap1 + EPS))
		n->y = 1;
	else if ((v.z > obj->cap2 - EPS && v.z < obj->cap2 + EPS) ||
			(v.z > obj->cap1 - EPS && v.z < obj->cap1 + EPS))
		n->z = 1;
}

void	swap_cap(t_obj *obj)
{
	int		save;

	save = 0;
	if (obj->cap1 > obj->cap2)
	{
		save = obj->cap1;
		obj->cap1 = obj->cap2;
		obj->cap2 = save;
	}
}

void	trace_cube_extend(t_obj *obj, t_vector o, t_vector v, float t[2])
{
	sub_vector(&o, &obj->pos);
	swap_cap(obj);
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
		t[0] = (obj->cap1 - o.y) / v.y;
		t[1] = (obj->cap2 - o.y) / v.y;
	}
	else
	{
		t[0] = (obj->cap2 - o.y) / v.y;
		t[1] = (obj->cap1 - o.y) / v.y;
	}
}

void	trace_cube_extend_z(t_obj *obj, t_vector o, t_vector v, float t[2])
{
	if (t[0] > obj->x1)
		obj->x1 = t[0];
	if (t[1] < obj->x2)
		obj->x2 = t[1];
	if (v.z >= 0)
	{
		t[0] = (obj->cap1 - o.z) / v.z;
		t[1] = (obj->cap2 - o.z) / v.z;
	}
	else
	{
		t[0] = (obj->cap2 - o.z) / v.z;
		t[1] = (obj->cap1 - o.z) / v.z;
	}
	if (obj->x1 > t[1] || t[0] > obj->x2)
		obj->dst = -1;
}

void	trace_cube(t_obj *obj, t_vector o, t_vector v)
{
	float		t[2];
	t_equation	eq;

	trace_cube_extend(obj, o, v, t);
	if (obj->x1 > t[1] || t[0] > obj->x2)
		obj->dst = -1;
	else
		trace_cube_extend_z(obj, o, v, t);
	if (t[0] > obj->x1)
		obj->x1 = t[0];
	if (t[1] < obj->x2)
		obj->x2 = t[1];
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
}
