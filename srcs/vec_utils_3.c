/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouilly <jrouilly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 22:12:54 by jrouilly          #+#    #+#             */
/*   Updated: 2017/02/15 13:07:50 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		not_vec(t_vector *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}

float		vec_len(t_vector *v)
{
	return (sqrtf(vec_dot(v, v)));
}

void		normalize(t_vector *v)
{
	float	len;

	len = vec_len(v);
	v->x = v->x / len;
	v->y = v->y / len;
	v->z = v->z / len;
}

t_vector	*refract_vector(t_vector *v, t_vector *o, float ref1, t_obj *obj)
{
	float		angle1;
	float		angle2;
	t_vector	n;

	obj->normale(&n, o, obj);
	angle1 = vec_dot(v, &n);
	angle2 = asin(ref1 * sin(angle1) / obj->refract_ind);
	v->x = (v->x + cos(angle1) * n.x) * sin(angle2) / sin(angle1) -
		n.x * cos(angle2);
	v->y = (v->y + cos(angle1) * n.y) * sin(angle2) / sin(angle1) -
		n.y * cos(angle2);
	v->z = (v->z + cos(angle1) * n.z) * sin(angle2) / sin(angle1) -
		n.z * cos(angle2);
	return (v);
}

void			translate_vector(t_vector *origin, t_vector *dest, float dst)
{
	origin->x += dst * dest->x;
	origin->y += dst * dest->y;
	origin->z += dst * dest->z;
}
