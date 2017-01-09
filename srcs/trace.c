/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 13:36:02 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/09 12:08:42 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_vec	calc_point(t_ray *ray)
{
	t_vec	point;

	point.x = VDIR.x * RDIST + ray->pos.x;
	point.y = VDIR.y * RDIST + ray->pos.y;
	point.z = VDIR.z * RDIST + ray->pos.z;
	return (point);
}

t_vec	calc_reflect_vect(t_ray *ray, t_obj *obj, t_vec point)
{
	t_vec	norm;
	t_vec	vdir_reflect;

	norm = default_n();
	if (obj->type == 's')
		norm = normalize(calc_vec(obj->vec1, point));
	else if (obj->type == 'p')
		norm = obj->vec2;
	else if (obj->type == 'c')
		norm = normalize(calc_ncylinder(ray, obj));
	else if (obj->type == 'k')
		norm = normalize(calc_ncone(ray, obj));
	vdir_reflect = normalize(reflect_vec(ray->vecdir, norm));
	return (vdir_reflect);
}

void		reflect_ray(t_ray *ray, t_obj *obj, t_vec point)
{
	ray->pos = point;
	ray->vecdir = calc_reflect_vect(ray, obj, point);
	ray->dist = 1000000;
}

t_color		trace(t_env *env, t_ray *ray, int i)
{
	t_color		color;
	t_color		color2;
	t_obj		*obj;
	t_vec	point;

	obj = NULL;
	color = init_color_black();
	if (i > MAX_DEPTH)
		return (color);
	if ((obj = test_obj(env, ray)) == NULL)
		return (color);
	point = calc_point(ray);
	RCOLOR = init_color_black();
	if (obj->reflect == 1)
	{
		reflect_ray(ray, obj, point);
		color = test_spot(env, ray, obj, point);
		color2 = trace(env, ray, i + 1);
		//color = trace(env, ray, i + 1);
		color_mix_float(&color, &color2, 0.35);
		return (color);
	}
	color = test_spot(env, ray, obj, point);
	return (color);
}
