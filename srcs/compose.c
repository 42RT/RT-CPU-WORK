/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:08:59 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/16 15:14:30 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		compose_neg_sphere(t_env *env, t_ray *ray, float dist)
{
	t_vec	pos;
	t_vec	point;
	t_vec	x;
	float	d;

	pos = add_vec(POS, COMPOSEPOS);
	point.x = VDIR.x * dist + ray->pos.x;
	point.y = VDIR.y * dist + ray->pos.y;
	point.z = VDIR.z * dist + ray->pos.z;
	x = calc_vec(pos, point);
	d = get_dist(x);
	if (d < env->obj->compose->r)
		return (1);
	return (0);
}

int		compose_neg_plane(t_env *env, t_ray *ray, float dist)
{
	t_vec	x;
	t_vec	point;
	t_vec	pos;
	float	d;

	pos = add_vec(POS, COMPOSEPOS);
	point.x = VDIR.x * dist + ray->pos.x;
	point.y = VDIR.y * dist + ray->pos.y;
	point.z = VDIR.z * dist + ray->pos.z;
	x = calc_vec(point, pos);
	d = dot(x, COMPOSEN);
	if (d < 0)
		return (1);
	return (0);
}

int		compose_obj(t_env *env, t_ray *ray, float dist)
{
	if (env->obj->compose != NULL)
	{
		env->obj->compose = env->obj->compose->first;
		while (env->obj->compose->next != NULL)
		{
			if (env->obj->compose->type == 'p' && compose_neg_plane(env, ray, dist) == 1)
				return (1);
			if (env->obj->compose->type == 's' && compose_neg_sphere(env, ray, dist) == 1)
				return (1);
			env->obj->compose = env->obj->compose->next;
		}
		if (env->obj->compose->type == 'p' && compose_neg_plane(env, ray, dist) == 1)
			return (1);
		if (env->obj->compose->type == 's' && compose_neg_sphere(env, ray, dist) == 1)
			return (1);
	}
	return (0);
}
