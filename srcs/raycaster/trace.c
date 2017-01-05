/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:36:02 by rfriscca          #+#    #+#             */
/*   Updated: 2016/12/16 16:16:32 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	calc_point(t_ray *ray)
{
	t_vector	point;

	point.x = VDIR.x * RDIST + ray->pos.x;
	point.y = VDIR.y * RDIST + ray->pos.y;
	point.z = VDIR.z * RDIST + ray->pos.z;
	return (point);
}

t_vector	calc_reflect_vect(t_ray *ray, t_obj *obj, t_vector point)
{
	t_vector	norm;
	t_vector	vdir_reflect;

	norm = default_n();
	if (obj->type == 's')
		norm = normalize_vec(calc_vect(obj->vec1, point));
	else if (obj->type == 'p')
		norm = obj->vec2;
	else if (obj->type == 'c')
		norm = normalize_vec(calc_ncylinder(ray, obj));
	else if (obj->type == 'k')
		norm = normalize_vec(calc_ncone(ray, obj));
	vdir_reflect = normalize_vec(reflect_vect(ray->vecdir, norm));
	return (vdir_reflect);
}

void		reflect_ray(t_ray *ray, t_obj *obj, t_vector point)
{
	ray->pos = point;
	ray->vecdir = calc_reflect_vect(ray, obj, point);
	ray->dist = 1000000;
}

t_color		trace(t_env *env, t_ray *ray, int i)
{
	t_color		color;
	t_obj		*obj;
	t_vector	point;

	obj = NULL;
	color = init_color_black();
	if (i > MAX_DEPTH)
		return (color);
	if ((obj = test_obj(env, ray)) == NULL)
		return (color);
	point = calc_point(ray);
	if (obj->reflect == 1)
	{
		reflect_ray(ray, obj, point);
		color = trace(env, ray, i + 1);
		return (color);
	}
	color = test_spot(env, ray, obj, point);
	return (color);
}
