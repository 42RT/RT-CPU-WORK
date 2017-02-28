/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/16 18:52:35 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/31 15:29:54 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <raytracer.h>

void		rotate_vector(t_vector *v, float ang_x, float ang_y, float ang_z)
{
	float	x;
	float	y;

	if (ang_x)
	{
		y = v->y;
		v->y = v->y * cos(ang_x) - v->z * sin(ang_x);
		v->z = y * sin(ang_x) + v->z * cos(ang_x);
	}
	if (ang_y)
	{
		x = v->x;
		v->x = v->x * cos(ang_y) + v->z * sin(ang_y);
		v->z = -x * sin(ang_y) + v->z * cos(ang_y);
	}
	if (ang_z)
	{
		x = v->x;
		v->x = v->x * cos(ang_z) - v->y * sin(ang_z);
		v->y = x * sin(ang_z) + v->y * cos(ang_z);
	}
}

void		add_vector(t_vector *v1, t_vector *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

void		sub_vector(t_vector *v1, t_vector *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
}

float		vec_dot(t_vector *v, t_vector *n)
{
	return (v->x * n->x + v->y * n->y + v->z * n->z);
}

float		vec_dot_abs(t_vector *v, t_vector *n)
{
	float	res;

	res = v->x * n->x + v->y * n->y + v->z * n->z;
	return (res >= 0 ? res : -res);
}
