/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 20:44:31 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/13 13:42:04 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <raytracer.h>

void		mod_vector(t_obj *obj, t_vector *o, t_vector *v)
{
	sub_vector(o, &(obj->pos));
	rotate_vector2(o, &(obj->ang));
	rotate_vector2(v, &(obj->ang));
	exp_compute(o, &(obj->exp));
	exp_compute(v, &(obj->exp));
}

static void	cut_cylinder_cone(t_equation *eq, float *x1, float *x2)
{
	float	z;

	z = 0;
	if (eq->obj->type & (CYLINDER | CONE | GLASS))
	{
		z = eq->v.z * *x1 + eq->o.z;
		if ((z < eq->obj->cap1 && z < eq->obj->cap2) ||
				(z > eq->obj->cap1 && z > eq->obj->cap2))
			*x1 = 1e8;
		z = eq->v.z * *x2 + eq->o.z;
		if ((z < eq->obj->cap1 && z < eq->obj->cap2) ||
				(z > eq->obj->cap1 && z > eq->obj->cap2))
			*x2 = 1e8;
	}
}

float		solve_equation(t_equation *eq)
{
	float	save;
//	float	x1;
//	float	x2;

	if (eq->delta >= 0 && eq->obj->type != CUBE)
	{
		eq->x1 = (-eq->b - sqrt(eq->delta)) / (2 * eq->a);
		eq->x2 = (-eq->b + sqrt(eq->delta)) / (2 * eq->a);
		eq->obj->x1 = eq->x1;
		eq->obj->x2 = eq->x2;
		if ((eq->obj->cap1 != 0 || eq->obj->cap2 != 0) 
			&& eq->obj->type & (CYLINDER | CONE | GLASS))
			cut_cylinder_cone(eq, &eq->x1, &eq->x2);
	}
	compose_obj(eq->obj, eq);
	if (eq->delta < 0)
		return (-1);
/*	if (eq->delta < 0)
		return (-1);
	else if (eq->delta == 0)
		return (-eq->b / (2 * eq->a));
	else
	{
		x1 = (-eq->b - sqrt(eq->delta)) / (2 * eq->a);
		x2 = (-eq->b + sqrt(eq->delta)) / (2 * eq->a);
		cut_cylinder_cone(eq, &x1, &x2);
		return ((x1 < x2) ? x1 : x2);
	}*/
	if (eq->x1 > eq->x2)
	{
		save = eq->x1;
		eq->x1 = eq->x2;
		eq->x2 = save;
	}
	if (eq->x1 > 1)
		return (eq->x1);
	else if (eq->x2 > 1)
		return (eq->x2);
	else
		return (1e8);
//	return ((eq->x1 < eq->x2) ? eq->x1 : eq->x2);
}
