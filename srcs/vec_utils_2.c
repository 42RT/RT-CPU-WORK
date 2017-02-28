/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 22:57:32 by jrouilly          #+#    #+#             */
/*   Updated: 2017/01/25 13:48:37 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <raytracer.h>

void		matrice_to_vector(t_vector *v, int **base)
{
	float	x;
	float	y;
	float	z;

	if (!base || !base[2])
		return ;
	x = v->x;
	y = v->y;
	z = v->z;
	v->x = (float)(x * base[0][0] + y * base[0][1] + z * base[0][2]);
	v->y = (float)(x * base[1][0] + y * base[1][1] + z * base[1][2]);
	v->z = (float)(x * base[2][0] + y * base[2][1] + z * base[2][2]);
}

void		rotate_vector2(t_vector *v, t_vector *r)
{
	float	x;
	float	y;

	if (r->x)
	{
		y = v->y;
		v->y = v->y * cos(r->x) - v->z * sin(r->x);
		v->z = y * sin(r->x) + v->z * cos(r->x);
	}
	if (r->y)
	{
		x = v->x;
		v->x = v->x * cos(r->y) + v->z * sin(r->y);
		v->z = -x * sin(r->y) + v->z * cos(r->y);
	}
	if (r->z)
	{
		x = v->x;
		v->x = v->x * cos(r->z) - v->y * sin(r->z);
		v->y = x * sin(r->z) + v->y * cos(r->z);
	}
}

t_vector	*cpy_vector(t_vector *src)
{
	t_vector	*res;

	res = (t_vector *)malloc(sizeof(t_vector));
	res->x = src->x;
	res->y = src->y;
	res->z = src->z;
	return (res);
}

void		vec_cpy(t_vector *src, t_vector *dest)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
}

void		exp_compute(t_vector *o, t_vector *exp)
{
	o->x /= exp->x;
	o->y /= exp->y;
	o->z /= exp->z;
}
