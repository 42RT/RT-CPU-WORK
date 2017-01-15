/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_spot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:15:57 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:11:57 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		lightcaster2(t_env *env, t_vec pos, t_ray ray)
{
	if (env->obj->type == 's')
		if (test_sphere2(env, pos, ray) == 1)
			return (1);
	if (env->obj->type == 'p')
		if (test_plan2(env, pos, ray) == 1)
			return (1);
	if (env->obj->type == 'c')
		if (test_cylinder2(env, pos, ray) == 1)
			return (1);
	if (env->obj->type == 'k')
		if (test_cone2(env, pos, ray) == 1)
			return (1);
	return (0);
}

int		lightcaster(t_env *env, t_vec pos, t_ray ray, t_obj *obj)
{
	env->obj = env->obj->first;
	while (env->obj->next)
	{
		if (lightcaster2(env, pos, ray) == 1)
		{
			env->obj = obj;
			return (1);
		}
		env->obj = env->obj->next;
	}
	if (lightcaster2(env, pos, ray) == 1)
	{
		env->obj = obj;
		return (1);
	}
	env->obj = obj;
	return (0);
}

t_ray	init_lightray(t_env *env, t_vec vecdir, t_vec point)
{
	t_vec	len;
	t_ray		ray;

	len = calc_vec(point, env->spot->spotpos);
	ray.vecdir = vecdir;
	ray.dist = sqrt(len.x * len.x + len.y * len.y + len.z * len.z);
	return (ray);
}

t_color	test_spot2(t_env *env, t_ray *ray, t_obj *obj, t_vec point)
{
	t_vec	vec_ltoo;
	t_vec	vec_otol;
	t_vec	vec_ctoo;
	double		angle;

	vec_ctoo = default_n();
	if (obj->type == 's')
		vec_ctoo = normalize(calc_vec(obj->vec1, point));
	else if (obj->type == 'p')
		vec_ctoo = obj->vec2;
	else if (obj->type == 'c')
		vec_ctoo = normalize(calc_ncylinder(ray, obj));
	else if (obj->type == 'k')
		vec_ctoo = normalize(calc_ncone(ray, obj));
	vec_ltoo = normalize(calc_vec(env->spot->spotpos, point));
	REFLECT = normalize(reflect_vec(vec_ltoo, vec_ctoo));
	vec_otol = normalize(calc_vec(point, env->spot->spotpos));
	angle = dot(vec_otol, vec_ctoo);
	env->spot->ray = init_lightray(env, vec_otol, point);
	if (lightcaster(env, point, env->spot->ray, env->obj) == 0)
		return (RCOLOR = calc_color(ray, obj->color_t, env->spot->color, angle));
	else
		return (RCOLOR = calc_shadow(ray, obj->color_t));
}

t_color	test_spot(t_env *env, t_ray *ray, t_obj *obj, t_vec point)
{
	t_color	color;

	color = init_color_black();
	while (env->spot->next)
	{
		color = test_spot2(env, ray, obj, point);
		env->spot = env->spot->next;
	}
	color = test_spot2(env, ray, obj, point);
	env->spot = env->spot->first;
	return (color);
}
