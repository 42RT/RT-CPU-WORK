/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfriscca <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 14:53:23 by rfriscca          #+#    #+#             */
/*   Updated: 2017/01/06 14:06:56 by rfriscca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	create_plan(t_env *env, t_vec pos, t_color color, t_vec n)
{
	t_obj	*obj;

	if ((obj = (t_obj*)malloc(sizeof(t_obj))) == NULL)
		error(1);
	obj->type = 'p';
	obj->vec1 = pos;
	obj->vec2 = n;
	obj->r = 0;
	obj->reflect = 0;
	obj->d1 = 0;
	obj->d2 = 0;
	obj->color_t = color;
	obj->next = NULL;
	if (env->obj == NULL)
	{
		obj->first = obj;
		env->obj = obj;
	}
	else
	{
		obj->first = env->obj->first;
		while (env->obj->next != NULL)
			env->obj = env->obj->next;
		env->obj->next = obj;
	}
	env->obj = env->obj->first;
}

t_obj	*test_plan(t_env *env, t_ray *ray)
{
	double		dist;
	t_vec	x;

	x = calc_vec(POS, ray->pos);
	dist = -dot(x, N) / dot(VDIR, N);
	if (dist > EPS && dist < RDIST)
	{
		RDIST = dist;
		return (env->obj);
	}
	return (NULL);
}

int		test_plan2(t_env *env, t_vec pos, t_ray ray)
{
	double		dist;
	t_vec	x;

	x = calc_vec(POS, pos);
	dist = -dot(x, N) / dot(ray.vecdir, N);
	if (dist > EPS && dist < ray.dist)
		return (1);
	return (0);
}
